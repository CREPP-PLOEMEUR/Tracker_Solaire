#include "GNSS.h"


static NMEA_MessageType nmea_messageTypes[NMEA_MESSAGE_TYPE_NUMBER] = 
{
    NMEA_MessageType{"GGA"},
    NMEA_MessageType{"GLL"},
    NMEA_MessageType{"GSA"},
    NMEA_MessageType{"GSV"},
    NMEA_MessageType{"RMC"},
    NMEA_MessageType{"VTG"}
};


static NMEA_Source nmea_sources[NMEA_SOURCE_NUMBER] = 
{
    NMEA_Source{"GP", "GPS"},
    NMEA_Source{"LL", "GALILEO"},
    NMEA_Source{"GL", "GLONASS"},
    NMEA_Source{"GB", "BEIDOU"},
    NMEA_Source{"GN", "GNSS - Mix"}
};


GNSS::GNSS(GNSS_Pin_Rx rx_Pin, GNSS_Pin_Tx tx_Pin, GNSS_Baudrate gnss_baudrate) : _rx_Pin{rx_Pin}, _tx_Pin{tx_Pin}, _gnss_baudrate{gnss_baudrate}
{
    //init UART communication
    //_uartDevice = new SoftwareSerial(_rx_Pin, _tx_Pin);
    Serial.begin(_gnss_baudrate);

}

void GNSS::setDebugChannel(HardwareSerial *serial, unsigned long baudrate)
{
  _uartDebug = serial;
  _uartDebug->begin(baudrate);
}


void GNSS::setDebugState(GNSS_DebugState debugState) 
{
    this->_debugState = debugState;
}

void GNSS::debug(String debugData)
{
    //_uartDebug->
}

inline byte calculateChecksum(byte *data, int length) {
  byte checksumA = 0;
  byte checksumB = 0;

  for (int i = 0; i < length; i++) {
    checksumA = checksumA + data[i];
    checksumB = checksumB + checksumA;
  }

  return checksumA;
}
void GNSS::init()
{
  //Serial.println("$PUBX,40,GLL,0,0,0,0*5C");
  //Header of 0xB5 0x62 0x06 0x08
  byte ubxCommand[] = {0xB5,0x62,0x06,0x08,0x06,0x00,0xC8,0x00,0x01,0x00,0x01,0x00,0xDE,0x6A};

  
   // 0x06, 0x08,    0x06, 0x00,     0xE8, 0x03,     0x01, 0x00, 0x00, 0x00,   0x00, 0x00,    0x00, 0x00,0x00, 0x00 
  // Calculer le checksum
  // Envoyer la commande UBX avec le checksum
    Serial.println("PUBX,41,1,3,3,38400,0");
    Serial.write(ubxCommand, sizeof(ubxCommand));

   //Serial.write();

    Serial.write(ubxCommand, sizeof(ubxCommand));
    Serial.println(GNSS_setUpdateRate());
    //Serial.write(0xB562060806006400010001001111);
}


void GNSS::startGNSS()
{
  Serial.println(GNSS_MODULE_WAKE_UP);
}

void GNSS::stopGNSS()
{
  Serial.println(GNSS_MODULE_SLEEP);
}


GNSS_Coordinates GNSS::getCoordinates()
{
  GNSS_Coordinates tmpCoordinates = {m_gnss_data.coordinates.latitude, m_gnss_data.coordinates.longitude};
  return tmpCoordinates;

}


String GNSS::extractField(NMEA_Frame data, uint8_t indexOfData)
{
  uint8_t frameSizeData = m_nmea_parser.countOfDelimiters;//getCountDelimiters(data) - 1;

  if(indexOfData+1 > frameSizeData)
  {
    return "<ERROR>";
  }
  else
  {

    if(indexOfData == 0)
    {
      return "INDEX_DATA_NULL";
    }
    else 
    {
      uint8_t startDelimiterAddress = m_nmea_parser.indexOfDelimiters[indexOfData-1];
      uint8_t endDelimiterAddress = m_nmea_parser.indexOfDelimiters[indexOfData];

      if(1 == 5)
      {
        return "eRRRDEKDEHDE";
      }
      else 
      {
        String returnValue = "";
        for(uint8_t index = startDelimiterAddress+1; index < endDelimiterAddress; index ++)
        {
          returnValue += data[index];
        }
        return returnValue;

      }
    }
    
    

  }
}

bool GNSS::readData(void)
{


  do
  {
    //Timout
    //_uartDebug->println("waiting data...");   
    //delay(1000);
  }while(!Serial.available());

  while (Serial.available()) {

        char c = Serial.read();

        if (c == m_nmea_settings.header) 
        {
            NMEA_Frame frame = Serial.readStringUntil('\n');
            bool error = true;
            for(uint8_t i = 0; i<frame.length();i++)
            {
              if(frame[i] == m_nmea_settings.footer)
              {
                error = false;
              }
            }

            if(error == false)
            {
            this->parseString(frame);   
           //_uartDebug->println(frame);     
            }
            else {
             // _uartDebug->println("INVALIDE_ANSWER");
            }
   
        }
        else {

        }
    }

    return true;
}


GNSS_Date GNSS::getDate()
{
  return m_gnss_data.date; 
}

GNSS_Time GNSS::getTime()
{
  return m_gnss_data.time;
}

bool GNSS::isValidPosition()
{
  return m_gnss_data.isReady;
}

void GNSS::displayInformations(void)
{
  _uartDebug->println("GNSS.SOURCE = "+String(m_gnss_data.source.name));
  _uartDebug->println("GNSS.LATITUDE_DIR = "+String(m_gnss_data.coordinates.latitudeDirection));
  _uartDebug->println("GNSS.LONGITUDE_DIR = "+String(m_gnss_data.coordinates.longitudeDirection));
  _uartDebug->println("GNSS.TIME = "+String(m_gnss_data.time.hour)+" h "+String(m_gnss_data.time.minute));
  _uartDebug->println("GNSS.DATE = "+String(m_gnss_data.date.day)+"/"+String(m_gnss_data.date.month)+"/"+String(m_gnss_data.date.year));
  _uartDebug->println("GNSS.SATELLITES = "+String(m_gnss_data.satellitesNumber));
  _uartDebug->println("GNSS.ALTITUDE = "+String(m_gnss_data.altitude));

  _uartDebug->println("GNSS.LATITUDE = "+String(m_gnss_data.coordinates.latitude,5));
  _uartDebug->println("GNSS.LONGITUDE = "+String(m_gnss_data.coordinates.longitude,5 ));

   _uartDebug->println("MAPS = "+String(m_gnss_data.coordinates.latitude,5 )+","+String(m_gnss_data.coordinates.longitude,5));
}

void GNSS::parseString(NMEA_Frame data) 
{

 
  this->updateSource(data);
  this->updateMessageType(data);
  this->updateParser(data);

  

  // _uartDebug->println("TYPE="+String(m_gnss_data.messageType.name));
  if(m_gnss_data.messageType.name == nmea_messageTypes[0].name) //GGA
  {
    //Time
    //_uartDebug->println(data);
    updateTime(this->extractField(data, 1));

    m_gnss_data.satellitesNumber = this->extractField(data, 7).toInt();
    m_gnss_data.altitude = this->extractField(data, 9).toFloat();

  }
  else if(m_gnss_data.messageType.name == nmea_messageTypes[1].name) //GLL
  {

  }
  else if(m_gnss_data.messageType.name == nmea_messageTypes[2].name) //GSA
  {

  }
  else if(m_gnss_data.messageType.name == nmea_messageTypes[3].name) //GSV
  {

  }
  else if(m_gnss_data.messageType.name == nmea_messageTypes[4].name) //RMC
  {
    char latitudeDirection = this->extractField(data, 4)[0];  //Ok
    char longitudeDirection = this->extractField(data, 6)[0]; //OK

    m_gnss_data.coordinates.longitudeDirection = longitudeDirection;
    m_gnss_data.coordinates.latitudeDirection = latitudeDirection;

    float latitudeDegree = float(String(this->extractField(data, 3)[0]).toInt()*10) + float(String(this->extractField(data, 3)[1]).toInt()); //OK
    
    String tmpCoord = "";
    for(uint8_t a=2;a<=9;a++)
    {
      tmpCoord += this->extractField(data, 3)[a];
    }

    float latitudeMinute = tmpCoord.toFloat()/60.0;
    m_gnss_data.coordinates.latitude = latitudeDegree + latitudeMinute;

    float degLongitude = int(String(this->extractField(data, 5)[0]).toInt()*100) + int(String(this->extractField(data, 5)[1]).toInt()*10) + int(String(this->extractField(data, 5)[2]).toInt()*1);
    //_uartDebug->println("Deg : "+String(degLongitude));
    String tmpCoordLongitude = "";

    for(uint8_t a=3;a<=10;a++)
    {
      tmpCoordLongitude += this->extractField(data, 5)[a];
    }
 
    float longitudeMinute = tmpCoordLongitude.toFloat()/60.0;
    float longitudeDegree = degLongitude;

    m_gnss_data.coordinates.longitude = longitudeDegree + longitudeMinute;

    updateDate(this->extractField(data, 9));

    m_gnss_data.coordinates.longitude= ( longitudeDirection == 'W' ) ? -m_gnss_data.coordinates.longitude : m_gnss_data.coordinates.longitude;
    m_gnss_data.coordinates.latitude= ( latitudeDirection == 'S') ? -m_gnss_data.coordinates.latitude : m_gnss_data.coordinates.latitude;

    if(m_gnss_data.coordinates.longitude != 0.0 || m_gnss_data.coordinates.latitude)
    {
      m_gnss_data.isReady = true;
    }

  }

}



void GNSS::updateSource(NMEA_Frame frame)
{

 //Source (STRING)
  if(m_gnss_data.source.source != "")
  {
    return ;
  }
  for(uint8_t indexSource = 0 ; indexSource < NMEA_SOURCE_NUMBER; indexSource++)
  {

    if(frame.startsWith(nmea_sources[indexSource].source))
    {
      m_gnss_data.source = nmea_sources[indexSource];
      break;
    }      
  }
}


void GNSS::clearSource()
{
  m_gnss_data.source = {"", ""};
}



void GNSS::updateMessageType(NMEA_Frame frame)
{

  m_gnss_data.messageType = this->extractType(frame) ;

}
void GNSS::clearMessageType()
{
  m_gnss_data.messageType = {""};
}


void GNSS::updateParser(NMEA_Frame data)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < data.length(); i++) {
        if (data.charAt(i) == m_nmea_settings.delimiter) 
        {
            m_nmea_parser.indexOfDelimiters[count] = i;
            count++;
        }
    }
    m_nmea_parser.countOfDelimiters = count;

}

void GNSS::updateTime(String frame)
{

  if(frame.length()<6)
  {
    return ;
  }

  m_gnss_data.time.hour = (String(char(frame[0])) + String(char(frame[1]))).toInt();
  m_gnss_data.time.minute = (String(char(frame[2])) + String(char(frame[3]))).toInt();
  m_gnss_data.time.seconde = (String(char(frame[4])) + String(char(frame[5]))).toInt();

}

void GNSS::updateDate(String frame)
{
  if(frame.length()<6)
  {
    return ;
  }
  m_gnss_data.date.day = (String(char(frame[0])) + String(char(frame[1]))).toInt();
  m_gnss_data.date.month = (String(char(frame[2])) + String(char(frame[3]))).toInt();
  m_gnss_data.date.year = (String(char(frame[4])) + String(char(frame[5]))).toInt();

}

void GNSS::startSelfTest(void)
{
 // _uartDebug->begin(baudrate);

  bool result = this->readData();
 // _uartDebug->begin(">>> SELF_TEST ");

  if(result)
  {
    //_uartDebug->begin(">>> OK ");
  }
  else 
  {
 //  _uartDebug->begin(">>> FAIL ");
  }

  //Extract data

  m_gnss_data.isReady = true;

  
}


bool GNSS::isReady(void)
{
  return m_gnss_data.isReady;
}


NMEA_MessageType GNSS::extractType(NMEA_Frame frame) {


    NMEA_MessageType messageType = {String(frame[2])+String(frame[3])+String(frame[4])};
   
    return messageType;
}
