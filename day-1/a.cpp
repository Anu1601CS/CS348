#include <bits/stdc++.h>
using namespace std;
typedef pair<double, int> pdi;

struct source
{
	double sending_rate;
	int bandwidth;
};

int main()
{
	int numSource, i, j, a;
	double stime;
	cout<<"Enter the number of sources: ";
	cin>>numSource;
	cout<<"Enter sending rate and bandwidth of each source: \n";
	struct source tmp[numSource + 1];
	int arr[numSource + 1];
	double arr2[numSource + 1];

	for (i = 1; i <= numSource; i++)
		arr2[i] = 0.0;

	memset(arr, 0, sizeof(arr));

	for (i = 1; i <= numSource; i++)
	{
		double a;
		int b;
		cin>>a>>b;

		tmp[i].sending_rate = a;
		tmp[i].bandwidth = b;
	}

	cout<<"Enter bandwidth of sink: ";
	cin>>a;
	int sink_wid = a;
	cout<<"Enter packet size: ";
	int pkt;
	cin>>pkt;
	cout<<"Enter simulation time: ";
	cin>>stime;

	priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
	double snk_sp = ((double)pkt) / ((double)sink_wid);

	for (i = 1; i <= numSource; i++)
	{
		int k = stime * (double)tmp[i].sending_rate;
		double sp = ((double)pkt) / ((double)tmp[i].bandwidth);
		double c = 0.0;
		double k1 = 1 / (tmp[i].sending_rate);
		arr[i] = k;

		for (j = 1; j <= k; j++)
		{
			if (j == 1)
			{
				pq.push(make_pair(sp + k1, i));
				c = sp + k1;
				arr2[i] += sp;
			}
			else
			{
				if (c < (double)(j)*k1)
					c = (double)(j)*k1;
				else
					arr2[i] += (abs(c - (double)(j) * (double)k1));
				pq.push(make_pair(c + sp, i));
				arr2[i] += sp;
				c += sp;
			}
		}
	}

	double c = 0.0;
	j = 1;
	double tmp_tm = 0.0;

	while (!pq.empty())
	{
		pdi p = pq.top();

		if (j == 1)
		{
			arr2[p.second] += (snk_sp);
			c = (snk_sp) + p.first;
		}
		else
		{
			if (p.first >= c)
			{
				arr2[p.second] += (snk_sp);
				c = p.first;
			}
			else
			{
				arr2[p.second] += (snk_sp + abs(c - p.first));
			}

			c += snk_sp;
		}

		tmp_tm = p.first;
		j++;
		pq.pop();
	}

	cout<<"\nThe average delay of the sources:\n";
	cout<<"\nSource\t:\tAverage Delay\n";

	for (i = 1; i <= numSource; i++)
	{
		cout <<i << "\t:\t" << arr2[i] / arr[i] << "\n";
	}

	return 0;
}
