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

//keys: 1 == off, 2 == damper up, 3 == damper down, 4 == on
typedef multimap<int, Event *> EBTypeMap;

void CS302_Midi::el_to_nd()
{
	vector<ND *> unmatched(128, NULL);
	nd = new NDMap;
	NDMap::iterator ndit;
	EventList::iterator elit;
	ND* newnd;
	ND* damper = NULL;
	double aggtime = 0;
	for(elit = el->begin(); elit != el->end(); elit++) {
		
		if((*elit)->time != 0) aggtime += (*elit)->time;
		if((*elit)->key == 'O') {
			newnd = new ND;
			newnd->key = 'N';
			newnd->start = aggtime / 480;
			newnd->pitch = (*elit)->v1;
			newnd->volume = (*elit)->v2;
			unmatched[newnd->pitch] = newnd;
		}
		else if((*elit)->key == 'F') {
			unmatched[(*elit)->v1]->stop = aggtime / 480;
			nd->insert(pair<double, ND*>(unmatched[(*elit)->v1]->start, unmatched[(*elit)->v1]));
			unmatched[(*elit)->v1] = NULL;
		}
		else {
			if((*elit)->v1 == 1) {
				damper = new ND;
				damper->key = 'D';
				damper->start = aggtime / 480;
			}
			else {
				damper->stop = aggtime / 480;
				nd->insert(pair<double, ND*>(damper->start, damper));
				damper = NULL;
			}
		}
	}
	for(ndit = nd->begin(); ndit != nd->end(); ndit++) {
		if(ndit->second->key == 'N') {
			cout << "NOTE " << ndit->second->pitch << " " << ndit->second->volume << " " << ndit->second->start << " " << ndit->second->stop << endl;
		}
		else { 
			cout << "DAMPER " << ndit->second->start << " " << ndit->second->stop << endl;
		}
	}
	
}

void CS302_Midi::nd_to_el()
{
	map <double, EBTypeMap *> ebtime;
	map <double, EBTypeMap *>::iterator ebtimeit;
	map <double, EBTypeMap *>::iterator prev;
  	EBTypeMap::iterator ebtypeit;
	NDMap::iterator ndit;
	el = new EventList;
	EventList::iterator elit;
	Event *ne;
	int et;
	for(ndit = nd->begin(); ndit != nd->end(); ndit++) {
		if(rint(ndit->second->start * 480) != rint(ndit->second->stop * 480)) {
			if(ndit->second->key == 'N') {
				ne = new Event;
				ne->key = 'O';
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
				ne->key = 'F';
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
			else {
				ne = new Event;
				ne->key = 'D';
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


	for(ebtimeit = ebtime.begin(); ebtimeit != ebtime.end(); ebtimeit++) {
		//cout << ebtimeit->first << ":   " << endl;
		if(ebtimeit == ebtime.begin()) {
			et = rint(ebtimeit->first * 480);
		}
		else {
			et = rint(ebtimeit->first * 480) - rint(prev->first * 480);
		}
		for(ebtypeit = ebtimeit->second->begin(); ebtypeit != ebtimeit->second->end(); ebtypeit++) {
			if(ebtypeit != ebtimeit->second->begin()) ebtypeit->second->time = 0;
			else ebtypeit->second->time = et;
			el->push_back(ebtypeit->second);
		}
		prev = ebtimeit;
	}
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
