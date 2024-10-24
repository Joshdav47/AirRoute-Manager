/*
 * Date:    2022/11/10
 * Authors: Damien Beatson, Joshua Davis
 * Desc: A program to test the functions of the airport program.
 */

#include "airport.h"

const Airport exampleOne = {
    "KMOT",    "Public",    "Minot International Airport",
    48.257778, -101.278056, 1716,
    "Minot",   "USA"};

const Airport exampleTwo = {"KOMA",  "Public", "Epply Airfield", 41.3,
                            -95.895, 984,      "Omaha",          "USA"};

const Airport exampleThree = {"PUGA",
                              "US Air Force Base",
                              "Anderson Air Force Base",
                              13.576111,
                              144.924444,
                              618,
                              "Yigo",
                              "USA"};

int compareAirports(const Airport *firstAirport, const Airport *secondAirport);

int main() {

  double testsPassed = 0;
  double tests = 15;

  // create airport test 1
  Airport *createAirportTest1 = createAirport("KMOT", "Public", "Minot International Airport", 48.257778,
                    -101.278056, 1716, "Minot", "USA");
  testsPassed += compareAirports(createAirportTest1, &exampleOne);

  // create airport test 2
  Airport *createAirportTest2 = createAirport(
      "KOMA", "Public", "Epply Airfield", 41.3, -95.895, 984, "Omaha", "USA");
  testsPassed += compareAirports(createAirportTest2, &exampleTwo);

  // create airport test 3
  Airport *createAirportTest3 = createAirport("PUGA", "US Air Force Base", "Anderson Air Force Base",
                    13.576111, 144.924444, 618, "Yigo", "USA");
  testsPassed += compareAirports(createAirportTest3, &exampleThree);

  // init airport test 1
  Airport *initAirportTest1 = malloc(sizeof(Airport));
  initAirport(initAirportTest1, "KMOT", "Public", "Minot International Airport",
              48.257778, -101.278056, 1716, "Minot", "USA");
  testsPassed += compareAirports(initAirportTest1, &exampleOne);

  // init airport test 2
  Airport *initAirportTest2 = malloc(sizeof(Airport));
  initAirport(initAirportTest2, "KOMA", "Public", "Epply Airfield", 41.3,
              -95.895, 984, "Omaha", "USA");
  testsPassed += compareAirports(initAirportTest2, &exampleTwo);

  // init airport test 3
  Airport *initAirportTest3 = malloc(sizeof(Airport));
  initAirport(initAirportTest3, "PUGA", "US Air Force Base",
              "Anderson Air Force Base", 13.576111, 144.924444, 618, "Yigo",
              "USA");
  testsPassed += compareAirports(initAirportTest3, &exampleThree);

  // airport to string test 1
  char toStringOneExpected[] =
      "KMOT\nPublic\nMinot International "
      "Airport\n48.257778\n-101.278056\n1716\nMinot\nUSA";
  testsPassed += strcmp(airportToString(&exampleOne), toStringOneExpected) ? 0 : 1;

  // airport to string test 2
  char toStringTwoExpected[] =
      "KOMA\nPublic\nEpply Airfield\n41.300000\n-95.895000\n984\nOmaha\nUSA";
  testsPassed += strcmp(airportToString(&exampleTwo), toStringTwoExpected) ? 0 : 1;

  // airport to string test 3
  char toStringThreeExpected[] = "PUGA\nUS Air Force Base\nAnderson Air Force "
                                 "Base\n13.576111\n144.924444\n618\nYigo\nUSA";
  testsPassed += strcmp(airportToString(&exampleThree), toStringThreeExpected) ? 0 : 1;

  // get air distance test 1 KMOT to KOMA is 882.125594 kms
  double airDistance1 = getAirDistance(&exampleOne, &exampleTwo);
  double expectedAirDistance1 = 882.125594;
  if (fabs(airDistance1 - expectedAirDistance1) < 0.01) {
    testsPassed++;
  }

  // get air distance test 2 KMOT to PUGA is 10556.071687 kms
  double airDistance2 = getAirDistance(&exampleOne, &exampleThree);
  double expectedAirDistance2 = 10556.071687;
  if (fabs(airDistance2 - expectedAirDistance2) < 0.01) {
    testsPassed++;
  }

  // get air distance test 3 KOMA to PUGA is 11297.728240 kms
  double airDistance3 = getAirDistance(&exampleTwo, &exampleThree);
  double expectedAirDistance3 = 11297.728240;
  if (fabs(airDistance3 - expectedAirDistance3) < 0.01) {
    testsPassed++;
  }
  // get estimated travel time test 1

  const Airport *routeOne[] = {
      createAirport("KMOT", "Public", "Minot International Airport", 48.257778,
                    -101.278056, 1716, "Minot", "USA"),
      createAirport("KOMA", "Public", "Epply Airfield", 41.3, -95.895, 984,
                    "Omaha", "USA"),
      createAirport("PUGA", "US Air Force Base", "Anderson Air Force Base",
                    13.576111, 144.924444, 618, "Yigo", "USA")};

  double travelTime1 = getEstimatedTravelTime(*routeOne, 3, 540, 2);
  double expectedTravelTime1 = 26.555285;
  if (fabs(travelTime1 - expectedTravelTime1) < 0.01)
    testsPassed++;

  // get estimated travel time test 2

  const Airport *routeTwo[] = {
      createAirport("KMOT", "Public", "Minot International Airport", 48.257778,
                    -101.278056, 1716, "Minot", "USA"),
      createAirport("KOMA", "Public", "Epply Airfield", 41.3, -95.895, 984,
                    "Omaha", "USA"),
      createAirport("PUGA", "US Air Force Base", "Anderson Air Force Base",
                    13.576111, 144.924444, 618, "Yigo", "USA"),
      createAirport("KMOT", "Public", "Minot International Airport", 48.257778,
                    -101.278056, 1716, "Minot", "USA")};

  double travelTime2 = getEstimatedTravelTime(*routeTwo, 4, 600, 1.5);
  double expectedTravelTime2 = 42.393209;
  if (fabs(travelTime2 - expectedTravelTime2) < 0.01)
    testsPassed++;

  // get estimated travel time test 3

  const Airport *routeThree[] = {
      createAirport("KMOT", "Public", "Minot International Airport", 48.257778,
                    -101.278056, 1716, "Minot", "USA"),
      createAirport("KOMA", "Public", "Epply Airfield", 41.3, -95.895, 984,
                    "Omaha", "USA"),
      createAirport("PUGA", "US Air Force Base", "Anderson Air Force Base",
                    13.576111, 144.924444, 618, "Yigo", "USA"),
      createAirport("KOMA", "Public", "Epply Airfield", 41.3, -95.895, 984,
                    "Omaha", "USA")};

  double travelTime3 = getEstimatedTravelTime(*routeThree, 4, 400, 5);
  double expectedTravelTime3 = 73.693955;
  if (fabs(travelTime3 - expectedTravelTime3) < 0.01) {
    testsPassed++;
  }

  printf("Tests passed: %.0f, out of %.0f\n", testsPassed, tests);
  printf("Percentage: %.2f\n", testsPassed / tests);
  return 0;
}
/*
 * This function compares each element of an Airport structure to check if the
 * data in them is the same. One is returned if everything is the same, and zero
 * if there is a difference.
 */
int compareAirports(const Airport *firstAirport, const Airport *secondAirport) {
  if (strcmp(firstAirport->gpsId, secondAirport->gpsId) != 0)
    return 0;
  if (strcmp(firstAirport->type, secondAirport->type) != 0)
    return 0;
  if (strcmp(firstAirport->name, secondAirport->name) != 0)
    return 0;
  if (firstAirport->latitude != secondAirport->latitude)
    return 0;
  if (firstAirport->longitude != secondAirport->longitude)
    return 0;
  if (firstAirport->elevationFeet != secondAirport->elevationFeet)
    return 0;
  if (strcmp(firstAirport->city, secondAirport->city) != 0)
    return 0;
  if (strcmp(firstAirport->countryAbbrv, secondAirport->countryAbbrv) != 0)
    return 0;

  return 1;
}