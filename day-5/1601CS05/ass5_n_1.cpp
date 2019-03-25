// Name: Anurag
// Roll no: 1601CS05

#include <bits/stdc++.h>
using namespace std;

class source
{
  public:
	int bnd_width;
};

class pkt
{
  public:
	int parent;
	int id;
};

class event_occ
{
  public:
	pkt p;
	double time;
};

class cmp
{
  public:
	bool operator()(event_occ e1, event_occ e2)
	{
		return e1.time > e2.time;
	}
};

int n;
int sz;
int qu_sz;
int mx_ss;

int main()
{
	cin >> n;
	int pkt_reach[n + 1];
	memset(pkt_reach, 0, sizeof(pkt_reach));
	int i;

	struct source src[n + 1];
	int last_sent[n + 1];
	int last_ack[n + 1];
	double cwnd[n + 1];

	for (i = 1; i <= n; i++)
	{
		cwnd[i] = 1.0;
		last_sent[i] = 0;
		last_ack[i] = 0;
	}

	double rtt[n + 1];
	cin >> sz;

	for (i = 1; i <= n; i++)
		cin >> src[i].bnd_width;

	cin >> qu_sz;

	for (i = 1; i <= n; i++)
		cin >> rtt[i];

	cin >> mx_ss;

	int tm;
	int j;
	priority_queue<event_occ, vector<event_occ>, cmp> pq;
	vector<double> v1;

	for (tm = 1; tm <= 1000000; tm++)
	{
		for (j = 1; j <= n; j++)
		{
			if ((double)last_sent[j] - (double)last_ack[j] < cwnd[j])
			{
				event_occ e_tmp;
				e_tmp.time = (double)tm + ((double)sz / (double)src[j].bnd_width) + rtt[j];
				e_tmp.p.parent = j;
				++last_sent[j];
				if (pq.size() < qu_sz)
				{
					pq.push(e_tmp);
					cwnd[j] += 1.0;
				}
				else
				{
					last_sent[j] = last_ack[j];
					cwnd[j] = 1.0;
				}
			}
		}

		v1.push_back(cwnd[2]);
		event_occ e_tmp;
		if (pq.size() != 0)
			e_tmp = pq.top();

		while (pq.size() != 0 && e_tmp.time <= tm)
		{
			last_ack[e_tmp.p.parent]++;
			pq.pop();
			if (pq.size() == 0)
				break;
			e_tmp = pq.top();
		}
	}
	return 0;
}
