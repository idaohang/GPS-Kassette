#ifndef GPS_H
#define GPS_H

static double calcDistance(double lat1, double lat2, double long1, double long2) {

	double dx = 71.5 * (long1 - long2);
	double dy = 111.3 * (lat1 - lat2);
	dist =sqrt(dx * dx + dy * dy);	
	return dist;

}

int getDistance()
{

	return (int) calcDistance(..);
}

boolean amBestimungsort(int abstand)
{
	return (abstand <= 10);
}

#endif
