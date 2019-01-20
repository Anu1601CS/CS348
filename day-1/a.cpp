#include <bits/stdc++.h>
using namespace std;

class source
{
	public:
	double sending_rate;
	int bandwidth;
};

int main()
{
	int numSource, i, j, a;
	double stime;
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> global_queue;

	cout << "Number of sources: ";
	cin >> numSource;
	source src[numSource];
	int arr[numSource];
	double arr2[numSource];

	for (i = 0; i < numSource; i++)
		arr2[i] = 0.0;

	memset(arr, 0, sizeof(arr));

	cout << "Sending rate and bandwidth of each source: \n";
	for (i = 0; i < numSource; i++)
	{
		double a;
		int b;
		cin >> a >> b;

		src[i].sending_rate = a;
		src[i].bandwidth = b;
	}

	cout << "Bandwidth of sink: ";
	cin >> a;
	int sink_wid = a;
	cout << "Packet size: ";
	int pkt;
	cin >> pkt;
	cout << "Simulation time: ";
	cin >> stime;

	double snk_spd = ((double)pkt) / ((double)sink_wid);

	for (i = 0; i < numSource; i++)
	{
		int k = stime * (double)src[i].sending_rate;
		double src_spd = ((double)pkt) / ((double)src[i].bandwidth);
		double c = 0.0;
		double k1 = 1 / (src[i].sending_rate);
		arr[i] = k;

		for (j = 0; j < k; j++)
		{
			if (j == 0)
			{
				global_queue.push(make_pair(src_spd + k1, i));
				c = src_spd + k1;
				arr2[i] += src_spd;
			}
			else
			{
				if (c < (double)(j)*k1)
					c = (double)(j)*k1;
				else
					arr2[i] += (c - (double)(j) * (double)k1);
				global_queue.push(make_pair(c + src_spd, i));
				arr2[i] += src_spd;
				c += src_spd;
			}
		}
	}

	j = 0;
	double c = 0.0;
	double src_tm = 0.0;

	while (!global_queue.empty())
	{
		pair<double, int> p = global_queue.top();

		if (j == 0)
		{
			arr2[p.second] += (snk_spd);
			c = (snk_spd) + p.first;
		}
		else
		{
			if (p.first >= c)
			{
				arr2[p.second] += (snk_spd);
				c = p.first;
			}
			else
			{
				arr2[p.second] += (snk_spd + c - p.first);
			}

			c += snk_spd;
		}

		j++;
		src_tm = p.first;
		global_queue.pop();
	}

	cout << "\nThe average delay of the sources:\n";
	cout << "\nSource\t:\tAverage Delay\n";

	for (i = 0; i < numSource; i++)
	{
		cout << i << "\t:\t" << arr2[i] / arr[i] << "\n";
	}

	return 0;
}
