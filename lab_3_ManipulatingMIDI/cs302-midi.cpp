#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <list>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "cs302-midi.h"
using namespace std;


//copy data from the event file data structure(EventList) to the Note file data structure (NDMap)
void CS302_Midi::el_to_nd()
{
	vector<ND *> unmatched(128, NULL); // temporary data structure for new Note events, which stored here until we reach their end event
	nd = new NDMap; //data structure we are copying to, key is the start time, values is an ND *
	NDMap::iterator ndit;
	EventList::iterator elit;
	ND* newnd; // holds newly created ND*s that represent notes
	ND* damper = NULL; //holds newly created ND*s that represent damper events
	double aggtime = 0;	//stores timepoint we are at in the EventList data structure as it stores realtive times and NDMap stores absolute times
	
	//go through the EventList data struture and convert into the NDMap format and store it in the new NDMap
	for(elit = el->begin(); elit != el->end(); elit++) {
		
		if((*elit)->time != 0) aggtime += (*elit)->time; //if the event marks that a new length of time has elapsed, add that amound to the aggregate
		
		if((*elit)->key == 'O') { //if the event is an 'ON' event, create a new ND object and store the data in it, then put it into the temporary data structure
									//until we cant its correlate 'OFF' event
			newnd = new ND;
			newnd->key = 'N';
			newnd->start = aggtime / 480; //convert that start time from event to note/damper format
			newnd->pitch = (*elit)->v1;
			newnd->volume = (*elit)->v2;
			unmatched[newnd->pitch] = newnd;
		}
		else if((*elit)->key == 'F') {	//if the event is an 'OFF' event, find the correlate 'ON' event in the temporary data structure,
										//add the stop time to the ND object, and put the object in the NDMap with the start time as the key
										//erase the created ND in the temp data structure
			unmatched[(*elit)->v1]->stop = aggtime / 480;
			nd->insert(pair<double, ND*>(unmatched[(*elit)->v1]->start, unmatched[(*elit)->v1]));
			unmatched[(*elit)->v1] = NULL;
		}
		else {	//if the event not neither 'ON' nor 'OFF' it is a 'DAMPER'
			if((*elit)->v1 == 1) { //if it is a damper down event, create a new ND object, copy the data to it,  and store it in the temp variable
				damper = new ND;
				damper->key = 'D';
				damper->start = aggtime / 480;
			}
			else { 	//if it is a damper up event, add the stop time to the object and then put the object into the map with the start time as the key
					//delete the object stored in the temp variable
				damper->stop = aggtime / 480;
				nd->insert(pair<double, ND*>(damper->start, damper));
				damper = NULL;
			}
		}
	}

	//print to test
	for(ndit = nd->begin(); ndit != nd->end(); ndit++) {
		if(ndit->second->key == 'N') {
			cout << "NOTE " << ndit->second->pitch << " " << ndit->second->volume << " " << ndit->second->start << " " << ndit->second->stop << endl;
		}
		else { 
			cout << "DAMPER " << ndit->second->start << " " << ndit->second->stop << endl;
		}
	}
	
}

typedef multimap<int, Event *> EBTypeMap; //stores all events that happen at the same time point from the EventList data structure 
										 //keys: 1 == off, 2 == damper up, 3 == damper down, 4 == on


//copy data from the Note file data structure (NDMap) to the event file data structure(EventList)
void CS302_Midi::nd_to_el()
{
	map <double, EBTypeMap *> ebtime; //temporary data structure for Event objects, stores multimaps of all events at each timepoint indicated in the event file
	map <double, EBTypeMap *>::iterator ebtimeit;
	map <double, EBTypeMap *>::iterator prev; //iterator that points to previous event multimap, used to calculate elapsed time between two time points
  	EBTypeMap::iterator ebtypeit;
	NDMap::iterator ndit;
	el = new EventList; // data strucure we ary copying to, it is a list of event objects
	EventList::iterator elit;
	Event *ne; //variable that will hold pointers to newly created Event objects
	int et; //hold elapsed time between two time points held in ebtime, also holds numbers 1-4 that represent the type of event
			//the event type controls where the object should be stored in the multimap so that its easier to put them into 
			//the event list in the order specified

	//for every ND event in our data structure, extract the data, create a new Event object, and out the data in this object. Then put this event object
	//in the temporary data structure. 
	for(ndit = nd->begin(); ndit != nd->end(); ndit++) {
		if(rint(ndit->second->start * 480) != rint(ndit->second->stop * 480)) { //ignore Notes or dampers that have the same start and stop time
			
			//if it is a note event, create two new Events, one for note ON and one for note OFF, copy the data to the objects,
			//if there is already an index for the start time of an event, just store the event in the multimap at that index,
			//else create the new index with they key as the start time.
			if(ndit->second->key == 'N') { 
				ne = new Event;
				ne->key = 'O'; //O means note on event
				ne->time = ndit->second->start;
				ne->v1 = ndit->second->pitch;
				ne->v2 = ndit->second->volume;
				et = 4; 
				if(ebtime.find(ndit->second->start) == ebtime.end()) {
					ebtime.insert(pair<double, EBTypeMap *>(ndit->second->start, new EBTypeMap)).first->second->insert(pair<int, Event *>(et, ne));
				}
				else {
					ebtime.find(ndit->second->start)->second->insert(pair<int, Event *>(et, ne));
				}
				
				ne = new Event;
				ne->key = 'F'; //F means note off event
				ne->time = ndit->second->stop;
				ne->v1 = ndit->second->pitch;
				et = 1;
				if(ebtime.find(ndit->second->stop) == ebtime.end()) {
					ebtime.insert(pair<double, EBTypeMap *>(ndit->second->stop, new EBTypeMap)).first->second->insert(pair<int, Event *>(et, ne));
				}
				else {
					ebtime.find(ndit->second->stop)->second->insert(pair<int, Event *>(et, ne));
				}
			
			}
			//if it is a damper event, create two new Events, one for damper up and one for damper down, copy the data to the objects,
			//if there is already an index for the start time of an event, just store the event in the multimap at that index,
			//else create the new index with they key as the start time.
			else {
				ne = new Event;
				ne->key = 'D'; //D means damper event
				ne->time = ndit->second->start;
				ne->v1 = 1;
				et = 3;
				if(ebtime.find(ndit->second->start) == ebtime.end()) {
					ebtime.insert(pair<double, EBTypeMap *>(ndit->second->start, new EBTypeMap)).first->second->insert(pair<int, Event *>(et, ne));
				}
				else {
					ebtime.find(ndit->second->start)->second->insert(pair<int, Event *>(et, ne));
				}
				
				ne = new Event;
				ne->key = 'D';
				ne->time = ndit->second->stop;
				ne->v1 = 0;
				et = 2;
				if(ebtime.find(ndit->second->stop) == ebtime.end()) {
					ebtime.insert(pair<double, EBTypeMap *>(ndit->second->stop, new EBTypeMap)).first->second->insert(pair<int, Event *>(et, ne));
				}
				else {
					ebtime.find(ndit->second->stop)->second->insert(pair<int, Event *>(et, ne));
				}
			}
		}
	}

	//iterate through our temporary structure, for every time point in the structure, put the events stored in its multimap into the EventList
	for(ebtimeit = ebtime.begin(); ebtimeit != ebtime.end(); ebtimeit++) {
		//cout << ebtimeit->first << ":   " << endl;
		
		//if this is the first timepoint in our data structure, the time of the first event should be set to whatever time it starts at, coverted to Event file units
		if(ebtimeit == ebtime.begin()) {
			et = rint(ebtimeit->first * 480);
		}
		//else the time for the first event at the time point should be set to the difference between this and the previous timepoint
		else {
			et = rint(ebtimeit->first * 480) - rint(prev->first * 480);
		}

		//put every event from this timepoint into the EventList data structure. Only set the relative time of the first event,
		//the rest of the event times are 0. as specified in the lab instructions the events in every time point should be put 
		//in in this order: OFF, DAMPER UP, DAMPER DOWN, ON we have already ordered the events in this way by giving them a key 
		//for the multimap based on their event type
		for(ebtypeit = ebtimeit->second->begin(); ebtypeit != ebtimeit->second->end(); ebtypeit++) {
			if(ebtypeit != ebtimeit->second->begin()) ebtypeit->second->time = 0;
			else ebtypeit->second->time = et;
			el->push_back(ebtypeit->second);
		}
		prev = ebtimeit;
	}

	//print to test
	for(elit = el->begin(); elit != el->end(); elit++) {
		if((*elit)->key == 79) {
			cout << "ON " << (*elit)->time << " " << (*elit)->v1 << " " << (*elit)->v2 << endl;
		}
		else if((*elit)->key == 70) {
			cout << "OFF " << (*elit)->time << " " << (*elit)->v1 << " " << endl;
		}
		else {
			if((*elit)->v1 == 1) cout << "DAMPER " << (*elit)->time << " " << "DOWN" << endl;
			else cout << "DAMPER " << (*elit)->time << " " << "UP" << endl;
		}
	}

}
