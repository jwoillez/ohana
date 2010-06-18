#include <string>

#include "novas-dll.h"
extern "C" {
	#include "novas.h"
}

void DLLAPI LVtopo_star(const double LVjd_tt, const double LVdelta_t, const LVcat_entry *LVstar, const LVon_surface *LVposition, const short int LVaccuracy, double *LVra, double *LVdec)
{
	cat_entry star;
	on_surface position;

	std::string star_catalog;
	std::string star_starname;

	//Assemble (cat_entry)star
	star_catalog.insert(0,(char *)LStrBuf(*LVstar->catalog));
	star_catalog=star_catalog.substr(0,LStrLen(*LVstar->catalog));
	strcpy(star.catalog,star_catalog.c_str());
	star_starname.insert(0,(char *)LStrBuf(*LVstar->starname));
	star_starname=star_starname.substr(0,LStrLen(*LVstar->starname));
	strcpy(star.starname,star_starname.c_str());
	star.starnumber = LVstar->starnumber;
	star.ra = LVstar->ra;
	star.dec = LVstar->dec;
	star.promora = LVstar->promora;
	star.promodec = LVstar->promodec;
	star.parallax = LVstar->parallax;
	star.radialvelocity = LVstar->radialvelocity;

	//Assemble (on_sruface)poisition
	position.latitude = LVposition->latitude;
	position.longitude = LVposition->longitude;
	position.height = LVposition->height;
	position.temperature = LVposition->temperature;
	position.pressure = LVposition->pressure;

	topo_star(LVjd_tt,LVdelta_t,&star,&position,LVaccuracy,LVra,LVdec);
};

void DLLAPI LVequ2hor(const double LVjd_ut1, const double LVdelta_t, const short int LVaccuracy, const double LVx, const double LVy, LVon_surface *LVlocation, const double LVra, const double LVdec, const short int LVref_option, double *LVzd, double *LVaz, double *LVrar, double *LVdecr)
{
	on_surface location;
	location.latitude = LVlocation->latitude;
	location.longitude = LVlocation->longitude;
	location.height = LVlocation->height;
	location.temperature = LVlocation->temperature;
	location.pressure = LVlocation->pressure;

	equ2hor(LVjd_ut1, LVdelta_t, LVaccuracy, LVx, LVy, &location, LVra, LVdec, LVref_option, LVzd, LVaz, LVrar, LVdecr);
};