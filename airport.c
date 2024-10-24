#include "airport.h"

Airport *createAirport(const char *gpsId, const char *type, const char *name,
                       double latitude, double longitude, int elevationFeet,
                       const char *city, const char *countryAbbrv) {
  if (gpsId == NULL || type == NULL || name == NULL || city == NULL ||
      countryAbbrv == NULL) {
    return NULL;
  }
  Airport *airport = (Airport *)malloc(sizeof(Airport) * 1);

  airport->gpsId = (char *)malloc(sizeof(char) * (strlen(gpsId) + 1));
  strcpy(airport->gpsId, gpsId);

  airport->type = (char *)malloc(sizeof(char) * (strlen(type) + 1));
  strcpy(airport->type, type);

  airport->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(airport->name, name);

  airport->latitude = latitude;

  airport->longitude = longitude;

  airport->elevationFeet = elevationFeet;

  airport->city = (char *)malloc(sizeof(char) * (strlen(city) + 1));
  strcpy(airport->city, city);

  airport->countryAbbrv =
      (char *)malloc(sizeof(char) * (strlen(countryAbbrv) + 1));
  strcpy(airport->countryAbbrv, countryAbbrv);

  return airport;
}

void initAirport(Airport *airport, const char *gpsId, const char *type,
                 const char *name, double latitude, double longitude,
                 int elevationFeet, const char *city,
                 const char *countryAbbrv) {
  if (airport == NULL || gpsId == NULL || type == NULL || name == NULL ||
      city == NULL || countryAbbrv == NULL) {
    return;
  }

  airport->gpsId = (char *)malloc(sizeof(char) * (strlen(gpsId) + 1));
  strcpy(airport->gpsId, gpsId);

  airport->type = (char *)malloc(sizeof(char) * (strlen(type) + 1));
  strcpy(airport->type, type);

  airport->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(airport->name, name);

  airport->latitude = latitude;

  airport->longitude = longitude;

  airport->elevationFeet = elevationFeet;

  airport->city = (char *)malloc(sizeof(char) * (strlen(city) + 1));
  strcpy(airport->city, city);

  airport->countryAbbrv =
      (char *)malloc(sizeof(char) * (strlen(countryAbbrv) + 1));
  strcpy(airport->countryAbbrv, countryAbbrv);

  return;
}

char *airportToString(const Airport *a) {
  if (a != NULL) {
    char *airportToString = NULL;
    asprintf(&airportToString, "%s\n%s\n%s\n%f\n%f\n%d\n%s\n%s", a->gpsId,
             a->type, a->name, a->latitude, a->longitude, a->elevationFeet,
             a->city, a->countryAbbrv);
    return airportToString;
  }
  return NULL;
}

double getAirDistance(const Airport *origin, const Airport *destination) {

  if (origin == NULL || destination == NULL) {
    return 0.0;
  }

  double radius = 6371.0;

  double rLatitude1, rLatitude2, rLongitude1, rLongitude2;

  // converting to radians
  rLatitude1 = ((origin->latitude / 180.0)) * M_PI;
  rLatitude2 = ((destination->latitude) / 180.0) * M_PI;
  rLongitude1 = ((origin->longitude) / 180.0) * M_PI;
  rLongitude2 = ((destination->longitude) / 180.0) * M_PI;

  // math
  return acos(sin(rLatitude1) * sin(rLatitude2) +
              cos(rLatitude1) * cos(rLatitude2) *
                  cos(fabs(rLongitude1 - rLongitude2))) *
         radius;
}

double getEstimatedTravelTime(const Airport *stops, int size,
                              double aveKmsPerHour, double aveLayoverTimeHrs) {
  if (stops == NULL) {
    return 0.0;
  }
  if (size <= 0) {
    return 0.0;
  }
  double hours = 0;
  for (int i = 0; i < (size - 1); i++) {
    hours += aveLayoverTimeHrs;
    hours += getAirDistance(&stops[i], &stops[i + 1]) / aveKmsPerHour;
  }
  return hours - aveLayoverTimeHrs;
}