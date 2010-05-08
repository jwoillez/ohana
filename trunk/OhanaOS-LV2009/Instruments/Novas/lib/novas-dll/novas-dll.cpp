#include <string>

#include "novas-dll.h"
extern "C" {
	#include "novas.h"
}

void DLLAPI LVapp_star(double LVtjd, LVbody *LVearth, LVcat_entry *LVstar, double *LVra, double *LVdec)
{
	body earth;
	cat_entry star;
	std::string earth_name;
	std::string star_catalog;
	std::string star_starname;

	earth.type = LVearth->type;
	earth.number = LVearth->number;
	earth_name.insert(0,(char *)LStrBuf(*LVearth->name));
	earth_name=earth_name.substr(0,LStrLen(*LVearth->name));
	strcpy(earth.name,earth_name.c_str());

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

	app_star(LVtjd,&earth,&star,LVra,LVdec);
};

void DLLAPI LVtopo_star(double LVtjd, LVbody *LVearth, double LVdeltat, LVcat_entry *LVstar, LVsite_info *LVlocation, double *LVra, double *LVdec)
{
	body earth;
	cat_entry star;
	site_info location;

	std::string earth_name;
	std::string star_catalog;
	std::string star_starname;

	earth.type = LVearth->type;
	earth.number = LVearth->number;
	earth_name.insert(0,(char *)LStrBuf(*LVearth->name));
	earth_name=earth_name.substr(0,LStrLen(*LVearth->name));
	strcpy(earth.name,earth_name.c_str());

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

	location.latitude = LVlocation->latitude;
	location.longitude = LVlocation->longitude;
	location.height = LVlocation->height;
	location.temperature = LVlocation->temperature;
	location.pressure = LVlocation->pressure;

	topo_star(LVtjd,&earth,LVdeltat,&star,&location,LVra,LVdec);
};

void DLLAPI LVearthtilt(double LVtjd, double *LVmobl, double *LVtobl, double *LVeq, double *LVdpsi, double *LVdeps)
{
	earthtilt(LVtjd, LVmobl, LVtobl, LVeq, LVdpsi, LVdeps);
};

void DLLAPI LVsidereal_time(double LVjd_high, double LVjd_low, double LVee, double *LVgst)
{
	sidereal_time(LVjd_high, LVjd_low, LVee, LVgst);
};

void DLLAPI LVequ2hor(double LVtjd, double LVdeltat, double LVx, double LVy, LVsite_info *LVlocation, double LVra, double LVdec, short int LVref_option, double *LVzd, double *LVaz, double *LVrar, double *LVdecr)
{
	site_info location;
	location.latitude = LVlocation->latitude;
	location.longitude = LVlocation->longitude;
	location.height = LVlocation->height;
	location.temperature = LVlocation->temperature;
	location.pressure = LVlocation->pressure;

	equ2hor(LVtjd, LVdeltat, LVx, LVy, &location, LVra, LVdec, LVref_option, LVzd, LVaz, LVrar, LVdecr);
};