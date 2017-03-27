/*
	Date: November 17, 2015
	Description: This program contains necessary functions for the whole project,
				 such as perform GET request using CURL, parsing JSON data to CPP object.
*/

#include "stdafx.h"
#include "Thesis.h"
#include "string.h"
#include "afxwin.h"
#include <atlstr.h>
#include <stdlib.h>
#include <string>
#include <iostream>

CURL *curl;
CURLcode res;
Document response;
struct data s;
char errorMsg[] = "Server is not available!";
struct frg *frg_topData = NULL;
struct device *device_topData = NULL;
struct device_ports *device_ports_topData = NULL;
CString urlMe("http://localhost/thesisv2/index.php?");
CString urlCons("http://localhost/thesisv2/consumption.php");

int parseTimeToMin(int hr, int min, int ampm){
	int minToMn=0;
	if(ampm == 0){
		minToMn = hr*60;
		minToMn += min;
	}else if(ampm == 1 && hr == 12){
		minToMn = hr*60;
		minToMn += min;
	}else{
		minToMn = (hr+12)*60;
		minToMn += min;
	}

	return minToMn;
}

CStringA parseTime(int minutesPastMidnight){ // must cast to (const char *) to use
	int hour = 0;
	int minutes = 0;
	CString dummy_hour;
	CString dummy_minutes;

	hour = minutesPastMidnight/60;
	minutes = minutesPastMidnight%60;

	if(hour < 10){
		dummy_hour.Format(_T("0%d"), hour);
	}else{
		dummy_hour.Format(_T("%d"), hour);
	}
	if(minutes < 10){
		dummy_minutes.Format(_T("0%d"), minutes);
	}else{
		dummy_minutes.Format(_T("%d"), minutes);
	}

	CStringA dummy_1(dummy_hour+_T(":")+dummy_minutes);

	return dummy_1;
}

struct schedTime explodeTime(int minutesPastMidnight){
	struct schedTime toReturn;
	int hour = 0;
	int minutes = 0;

	hour = minutesPastMidnight/60;
	minutes = minutesPastMidnight%60;

	if(hour > 12){
		hour -= 12;
	}

	if(minutesPastMidnight > 719){
		toReturn.ampm = 1;
	}else{
		toReturn.ampm = 0;
	}

	toReturn.hour = hour;
	toReturn.minutes = minutes;

	return toReturn;
}

void insertDevice(int rooms_id, int device_id, int index){
	struct device *temp = NULL;

	temp = (struct device*)malloc(sizeof(struct device));
	temp->rooms_id = rooms_id;
	temp->device_id = device_id;
	temp->index = index;

	if(device_topData == NULL){
		temp->next = NULL;
	}else{
		temp->next = device_topData;
	}

	device_topData = temp;
}

struct device_ids searchDevice(int index){
	struct device_ids temp_ids;
	struct device *temp = NULL;

	temp_ids.device_id = 0;
	temp_ids.rooms_id = 0;

	if(device_topData != NULL){
		temp = device_topData;
		while(temp != NULL){
			if(temp->index == index){
				temp_ids.device_id = temp->device_id;
				temp_ids.rooms_id = temp->rooms_id;
				break;
			}
			temp = temp->next;
		}
	}

	return temp_ids;
}

void clearDevice(){
	free(device_topData);
	device_topData = NULL;
}

void insertData(int frg_id, int rooms_id, int floors_id, int row){
	struct frg *temp = NULL;

	temp = (struct frg*)malloc(sizeof(struct frg));
	temp->frg_id = frg_id;
	temp->rooms_id = rooms_id;
	temp->floors_id = floors_id;
	temp->row = row;

	if(frg_topData == NULL){
		temp->next = NULL;
	}else{
		temp->next = frg_topData;
	}

	frg_topData = temp;
}

struct frg_ids searchData(int row){
	struct frg *temp;
	struct frg_ids temp_ids;
	int toReturn = 0;

	temp_ids.floors_id = temp_ids.frg_id = temp_ids.rooms_id = temp_ids.status = 0;

	if(frg_topData != NULL){
		temp = frg_topData;
		while(temp != NULL){
			if(temp->row == row){
				temp_ids.frg_id = temp->frg_id;
				temp_ids.floors_id = temp->floors_id;
				temp_ids.rooms_id = temp->rooms_id;
				temp_ids.status = 1;
				break;
			}
			temp = temp->next;
		}
	}

	return temp_ids;
}

void clearData(){
	struct frg *temp;

	while(frg_topData != NULL){
		temp = frg_topData;
		frg_topData = frg_topData->next;
		free(temp);
	}
}

void init_string(struct data *s) {
	s->len = 0;
	s->string = (char *)malloc(s->len + 1);
	if (s->string == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	s->string[0] = '\0';
}

size_t writefunc(void *string, size_t size, size_t nmemb, struct data *s)
{
	size_t new_len = s->len + size*nmemb;
	s->string = (char *)realloc(s->string, new_len + 1);
	if (s->string == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}
	memcpy(s->string + s->len, string, size*nmemb);
	s->string[new_len] = '\0';
	s->len = new_len;

	return size*nmemb;
}

void thesis_start_request() {
	curl = curl_easy_init();
	init_string(&s);
}

void thesis_end_request() {
	curl_easy_cleanup(curl);
	free(s.string);
}

int thesis_request(const char *function) {
	int toReturn;

	thesis_start_request();

	curl_easy_setopt(curl, CURLOPT_URL, function);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
	res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		toReturn = 0;
	}
	else {
		response.Parse(s.string);
		toReturn = 1;
	}

	thesis_end_request();

	return toReturn;
}