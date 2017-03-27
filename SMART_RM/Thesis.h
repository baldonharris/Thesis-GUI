#include "curl/curl.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#ifndef THESIS_H
#define THESIS_H

using namespace rapidjson;

struct data {
	char *string;
	size_t len;
};

struct frg{
	int frg_id;
	int rooms_id;
	int floors_id;
	int row;
	struct frg *next;
};

struct frg_ids{
	int frg_id;
	int rooms_id;
	int floors_id;
	int status;
};

struct device{
	int rooms_id;
	int device_id;
	int index;
	struct device *next;
};

struct device_ids{
	int rooms_id;
	int device_id;
};

struct schedTime{
	int hour;
	int minutes;
	int ampm;
};

extern CURL *curl;
extern CURLcode res;
extern Document response;
extern struct data s;
extern char errorMsg[];
extern struct frg *frg_topData;
extern struct device *device_topData;
extern CString urlMe;
extern CString urlCons;

int thesis_request(const char *function);
void insertData(int frg_id, int rooms_id, int floors_id, int row);
struct frg_ids searchData(int row);
void clearData();
CStringA parseTime(int minutesPastMidnight);
void insertDevice(int rooms_id, int device_id, int index);
struct device_ids searchDevice(int index);
void clearDevice();
int parseTimeToMin(int hr, int min, int ampm);
struct schedTime explodeTime(int minutesPastMidnight);

#endif