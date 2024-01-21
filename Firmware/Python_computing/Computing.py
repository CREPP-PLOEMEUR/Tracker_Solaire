import re

def parse_gprmc_data(gprmc_frame):
    match = re.match(r'\$GPRMC,(\d+\.\d+),[AV],(\d+\.\d+),([NS]),(\d+\.\d+),([EW]),', gprmc_frame)
    
    if match:
        time, latitude, lat_direction, longitude, lon_direction = match.groups()
        
        latitude_decimal = float(latitude[:2]) + float(latitude[2:]) / 60.0
        longitude_decimal = float(longitude[:3]) + float(longitude[3:]) / 60.0
        
        if lat_direction == 'S':
            latitude_decimal = -latitude_decimal
        if lon_direction == 'W':
            longitude_decimal = -longitude_decimal
        
        return {'time': time, 'latitude': latitude_decimal, 'longitude': longitude_decimal}
    else:
        return None

# Exemple d'utilisation
gprmc_frame = "$GPRMC,130000.00,A,4745.57702,N,00329.76825,W"
parsed_data = parse_gprmc_data(gprmc_frame)

if parsed_data:
    print("Time:", parsed_data['time'])
    print("Latitude:", parsed_data['latitude'])
    print("Longitude:", parsed_data['longitude'])
else:
    print("Erreur de parsing de la trame GPRMC.gitbu")