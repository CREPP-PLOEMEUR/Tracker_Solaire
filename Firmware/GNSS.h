/**
 * @file GNSS.h
 * @author Nicolas Le Guerroue
 * @brief 
 * @version 1.0
 * @date 
 * 
 */
#ifndef GNSS_H
#define GNSS_H

#include "DateTime.h"
#include "NMEA.h"

/*!

*/
#define GNSS_NETWORK 5
#define GNSS_TYPE_ANSWER 5

#define GNSS_BAUDRATE_9600 9600
#define GNSS_BAUDRATE_38400 38400
#define GNSS_BAUDRATE_11520 11520

#define GNSS_DEFAULT_BAUDRATE GNSS_BAUDRATE_11520

#define GNSS_DEFAULT_RX_GNSS 8
#define GNSS_DEFAULT_TX_GNSS 9

#define GNSS_DEFAULT_DEBUG_STATE true
/*!
4745.57702 = 47 + 45*0.57702*60 = 45°42'34.6212"
0329.76825 = 3°29'46.095

47.759617, -3.4961375
47.75962, -3.4961375

*/


#define NMEA_GPGGA_EXAMPLE "GPGGA,130000.00,4745.57754,N,00329.76917,W,1,07,1.20,14.0,M,49A,3,23,17,05,15,24,13,22,,,,,,2.18,1.20,1.82*03"
#define NMEA_GPGSV_EXAMPLE "GPGSV,4,1,13,05,29,191,31,10,03,330,,12,00,200,,13,66,101,18*78,,15,73,289,21,17,12,098,30,18,07,273,*7E"
#define NMEA_GPRMC_EXAMPLE "GPRMC,130000.00,A,4745.57702,N,00329.76825,W,1.417,,031223,,,A*61"

// 47°45'34.6"N 3°29'46.1"W
//47.759617,-3.496137

#define GPS_LATITUDE_DEG 47
#define GPS_LATITUDE_SEC 75958

#define GPS_LONGITUDE_DEG 3
#define GPS_LONGITUDE_SEC 49623

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "NMEA.h"


/**
 * @brief GNSS class
 * 
 */
class GNSS 			
{
  public:

    typedef uint8_t GNSS_Pin_Rx;
    typedef uint8_t GNSS_Pin_Tx;
    typedef uint32_t GNSS_Baudrate;
    typedef bool GNSS_DebugState;
    
    /**
     * @brief Construct a new GNSS object
     * 
     * @param rx_Pin 
     * @param tx_Pin 
     * @param gnss_baudrate 
     */
    GNSS(GNSS_Pin_Rx rx_Pin, GNSS_Pin_Tx tx_Pin, GNSS_Baudrate gnss_baudrate);


    /**
     * @brief Set Debug Channel
     * 
     * @param serial : Serial object (reference)
     * @param baudrate : Baudrate of debug channel
     */
    void setDebugChannel(HardwareSerial *serial, uint32_t baudrate);


    /**
     * @brief Set the Debug State object
     * 
     * @param debugState :
     */
    void setDebugState(GNSS_DebugState debugState);

    
    void startSelfTest(void);

    
    bool isReady(void);
    const char* getStatus();

    bool getSignal(void);

    const char* getLatitude(void);
    const char* getLongitude(void);
    String getTime(void);
    String getDate(void);

    bool readData(void);
    void displayInformations(void);
    void init(void);

    void shutdown(void);

    void simulate(void);


    inline String hexToStr(uint16_t data)
    {
      return String(char((data >> 8) & 0xFF))+String(char(data & 0x00FF)); //COnvert 0x4141 -> en "AA"
    }

    typedef struct 
    {
      uint8_t latitudeDegree;
      float latitudeMinute;
      char latitudeDirection;

      uint8_t longitudeDegree;
      float longitudeMinute;
      char LongitudeDirection;

    } Coordinates;
    

  private:



    /**
     * @brief NMEA Settings
     * 
     */
    NMEA_Settings m_nmea_settings = {NMEA_DEFAULT_HEADER, NMEA_DEFAULT_DELIMITER, NMEA_DEFAULT_FOOTER};

    /**
     * @brief NMEA Frame (String alias)
     * 
     */
    NMEA_Frame m_nmea_frame {""};

    /**
     * @brief NMEA Parser (array of delimiters)
     * 
     */
    NMEA_Parser m_nmea_parser = {0, {}};



    /**
     * @brief GNSS Data
     * 
     */
    typedef struct 
    {
        NMEA_Source source;
        NMEA_MessageType messageType;
        uint8_t satellitesNumber;
        GNSS::Coordinates coordinates;
        uint16_t altitude;
        DateTime time;
        Date date;
        bool isReady;
        
    } GNSS_Data;


    GNSS_Data m_gnss_data = 
    {
      NMEA_Source{"", ""},
      NMEA_MessageType{""},
      0,
      GNSS::Coordinates{0, 'N', 0, 'E'},
      0,
      DateTime{0,0, 0},
      Date{0,0,0},
      false
    };




    SoftwareSerial *_uartDevice; 
    HardwareSerial *_uartDebug; //used when debugging


    GNSS_DebugState _debugState = GNSS_DEFAULT_DEBUG_STATE;
    GNSS_Pin_Rx _rx_Pin = GNSS_DEFAULT_RX_GNSS;
    GNSS_Pin_Tx _tx_Pin = GNSS_DEFAULT_TX_GNSS;
    GNSS_Baudrate _gnss_baudrate = GNSS_DEFAULT_BAUDRATE;



    void debug(String debugData);
    void parseString(NMEA_Frame data);

    void updateSource(NMEA_Frame data);
    void clearSource();

    void updateParser(NMEA_Frame data);

    void updateMessageType(NMEA_Frame data);
    void clearMessageType();
    
    


    //extractData
    String extractField(NMEA_Frame data, uint8_t indexOfData);
    void updateTime(String data);
    void updateDate(String frame);

    NMEA_MessageType extractType(NMEA_Frame frame);
    NMEA_Source extractSource(NMEA_Frame frame);

}; 


#endif