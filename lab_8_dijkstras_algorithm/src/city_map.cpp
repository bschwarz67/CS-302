#include <vector>
#include <math.h>
#include <list>
#include "city_map.hpp"

City_Map::City_Map() {

	Intersection *i;
	int street;
	int avenue;
	double x;
	double y;
	double green_street;
	double green_avenue;
	vector <vector <Intersection*> > m;
	vector <Intersection*> avenues;
	list <Intersection *>::iterator lit;
	Road_Segment *rs;


	last = NULL;
	while (!cin.fail()) {
		cin >> street >> avenue >> x >> y >> green_street >> green_avenue;
		if(!cin.fail()) {
			i = new Intersection();
			i->street = street;
			i->avenue = avenue;

			i->x = x;
			i->y = y;
			i->green[0] = green_street;
			i->green[1] = green_avenue;
			i->best_time = -1.0;
    		i->backedge = NULL;
			all.push_back(i);


			if(street == 0 && avenue == 0) first = i;
			if(last == NULL || (avenue >= last->avenue && street >= last->street)) last = i;
			cout << i->street << " " << i->avenue << endl;
		}
		
	}
	avenues.resize(last->avenue + 1, NULL);
	m.resize(last->street + 1, avenues);

	cout << m.size() << " " << m[0].size() << endl;

	for (lit = all.begin(); lit != all.end(); lit++) {
		i = *lit;
		//cout << i->street << " " <<  i->avenue << endl;
		m[i->street][i->avenue] = *lit;
		//cout << i->street << " " <<  i->avenue << endl;
  	}

	
	for (int j = 0; j < m.size(); j++) {
		for(int k = 0; k < m[0].size(); k++) {
			cout << j << k << endl;
			//street links
			if(j % 5 == 0) {
				if(k - 1 >= 0) {
					rs = new Road_Segment();
					rs->type = STREET;
					rs->number = j;
					rs->from = m[j][k];
					rs->to = m[j][k - 1];
					//calculate distance 
					if(rs->from->y == rs->to->y) rs->distance = abs(rs->from->x - rs->to->x);
					else rs->distance = sqrt(abs(rs->from->y - rs->to->y) * abs(rs->from->y - rs->to->y) + abs(rs->from->x - rs->to->x) * abs(rs->from->x - rs->to->x));
					m[j][k]->adj.push_back(rs);
				}
				if(k + 1 < m[0].size()) {
					rs = new Road_Segment();
					rs->type = STREET;
					rs->number = j;
					rs->from = m[j][k];
					rs->to = m[j][k + 1];
					//calculate distance 
					if(rs->from->y == rs->to->y) rs->distance = abs(rs->from->x - rs->to->x);
					else rs->distance = sqrt(abs(rs->from->y - rs->to->y) * abs(rs->from->y - rs->to->y) + abs(rs->from->x - rs->to->x) * abs(rs->from->x - rs->to->x));
					m[j][k]->adj.push_back(rs);

				}
			}
			else {
				if(j % 2 == 1 && k - 1 >= 0) {
					rs = new Road_Segment();
					rs->type = STREET;
					rs->number = j;
					rs->from = m[j][k];
					rs->to = m[j][k - 1];
					//calculate distance 
					if(rs->from->y == rs->to->y) rs->distance = abs(rs->from->x - rs->to->x);
					else rs->distance = sqrt(abs(rs->from->y - rs->to->y) * abs(rs->from->y - rs->to->y) + abs(rs->from->x - rs->to->x) * abs(rs->from->x - rs->to->x));
					m[j][k]->adj.push_back(rs);
				}
				if(j % 2 == 0 && k + 1 < m[0].size()) {
					rs = new Road_Segment();
					rs->type = STREET;
					rs->number = j;
					rs->from = m[j][k];
					rs->to = m[j][k + 1];
					//calculate distance 
					if(rs->from->y == rs->to->y) rs->distance = abs(rs->from->x - rs->to->x);
					else rs->distance = sqrt(abs(rs->from->y - rs->to->y) * abs(rs->from->y - rs->to->y) + abs(rs->from->x - rs->to->x) * abs(rs->from->x - rs->to->x));
					m[j][k]->adj.push_back(rs);

				}

			}


			//ave links

			if(k % 5 == 0 || k == m[0].size() - 1) {
				if(j - 1 >= 0) {
					rs = new Road_Segment();
					rs->type = AVENUE;
					rs->number = k;
					rs->from = m[j][k];
					rs->to = m[j - 1][k];
					//calculate distance 
					if(rs->from->x == rs->to->x) rs->distance = abs(rs->from->y - rs->to->y);
					else rs->distance = sqrt(abs(rs->from->y - rs->to->y) * abs(rs->from->y - rs->to->y) + abs(rs->from->x - rs->to->x) * abs(rs->from->x - rs->to->x));
					m[j][k]->adj.push_back(rs);
				}
				if(j + 1 < m.size()) {
					rs = new Road_Segment();
					rs->type = AVENUE;
					rs->number = k;
					rs->from = m[j][k];
					rs->to = m[j + 1][k];
					//calculate distance 
					if(rs->from->x == rs->to->x) rs->distance = abs(rs->from->y - rs->to->y);
					else rs->distance = sqrt(abs(rs->from->y - rs->to->y) * abs(rs->from->y - rs->to->y) + abs(rs->from->x - rs->to->x) * abs(rs->from->x - rs->to->x));
					m[j][k]->adj.push_back(rs);

				}
			}
			else {
				if(k % 2 == 1 && j - 1 >= 0) {
					rs = new Road_Segment();
					rs->type = AVENUE;
					rs->number = k;
					rs->from = m[j][k];
					rs->to = m[j - 1][k];
					//calculate distance 
					if(rs->from->x == rs->to->x) rs->distance = abs(rs->from->y - rs->to->y);
					else rs->distance = sqrt(abs(rs->from->y - rs->to->y) * abs(rs->from->y - rs->to->y) + abs(rs->from->x - rs->to->x) * abs(rs->from->x - rs->to->x));
					m[j][k]->adj.push_back(rs);
				}
				if(k % 2 == 0 && j + 1 < m.size()) {
					rs = new Road_Segment();
					rs->type = AVENUE;
					rs->number = k;
					rs->from = m[j][k];
					rs->to = m[j + 1][k];
					//calculate distance 
					if(rs->from->x == rs->to->x) rs->distance = abs(rs->from->y - rs->to->y);
					else rs->distance = sqrt(abs(rs->from->y - rs->to->y) * abs(rs->from->y - rs->to->y) + abs(rs->from->x - rs->to->x) * abs(rs->from->x - rs->to->x));
					m[j][k]->adj.push_back(rs);

				}

			}




			//cout << m[j][k]->street << m[j][k]->avenue << " ";
			//if(k == m[0].size() - 1) cout << endl;
		}
	}

}

double City_Map::Dijkstra(int avg_best_worst) {

	Intersection *i;
	Road_Segment *rs;
	list <Intersection *>::iterator lit_all;
	list <Road_Segment *>::iterator lit_adj;
	double d;
	vector <vector <int> > m;
	vector <int> avenues;

	avenues.resize(last->avenue + 1, 0);
	m.resize(last->street + 1, avenues);
		
	for (lit_all = all.begin(); lit_all != all.end(); lit_all++) {
		i = *lit_all;
		i->bfsq_ptr = bfsq.end();
	}
	
	i = first;
	i->best_time = 0.0;
	bfsq.insert(pair<double, Intersection *>(i->best_time,i));
	while(!bfsq.empty()) {
		i = bfsq.begin()->second;
		bfsq.erase(bfsq.begin());
		i->bfsq_ptr = bfsq.end();
		m[i->street][i->avenue] = 1;

		for (lit_adj = i->adj.begin(); lit_adj != i->adj.end(); lit_adj++) {
			rs = *lit_adj;
			if (avg_best_worst == 66) d = i->best_time + ((rs->distance / 30.0) * 3600);
			else if(avg_best_worst == 65) {

				if(rs->type == STREET) {
					d = i->best_time + ((rs->distance / 30.0) * 3600) + ((rs->to->green[1] * rs->to->green[1]) / (2 * (rs->to->green[0] + rs->to->green[1])));
				}
				else {
					d = i->best_time + ((rs->distance / 30.0) * 3600) + ((rs->to->green[0] * rs->to->green[0]) / (2 * (rs->to->green[0] + rs->to->green[1])));
				}
				
			}
			else {
				if(rs->type == STREET) {
					d = i->best_time + ((rs->distance / 30.0) * 3600) + rs->to->green[1];
				}
				else {
					d = i->best_time + ((rs->distance / 30.0) * 3600) + rs->to->green[0];
				}
			}

			//test if node had been visited before
			if(m[rs->to->street][rs->to->avenue] != 1) {
				if(rs->to->best_time == -1.0 || rs->to->best_time > d) {
					if(rs->to->best_time > d) bfsq.erase(rs->to->bfsq_ptr);
					rs->to->best_time = d;
					rs->to->backedge = rs;
					rs->to->bfsq_ptr = bfsq.insert(pair<double, Intersection *>(d,rs->to));
				}
			}
		}
	}
	
	

	rs = last->backedge;
	while(rs != NULL) {
		path.push_front(rs);
		rs = rs->from->backedge;
	}

	d = last->best_time;
	
	return d;
}
