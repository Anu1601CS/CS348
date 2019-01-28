// Name : Anurag
// Roll no: 1601CS05

#include <bits/stdc++.h>
using namespace std;

class source
{
  public:
	double sending_rate;
	int bandwidth;
};

priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> global_queue;

void cal(double arr2[], int numSource, double snk_spd, int arr[])
{

	int tmp1 = 0, i;
	double tmp2 = 0.0;
	double src_tm = 0.0;

	while (!global_queue.empty())
	{
		pair<double, int> p = global_queue.top();

		if (tmp1 == 0)
		{
			arr2[p.second] += snk_spd;
			tmp1 = snk_spd + p.first;
		}
		else
		{
			if (tmp2 <= p.first)
			{
				arr2[p.second] += snk_spd;
				tmp2 = p.first;
			}
			else
				arr2[p.second] += tmp2 + snk_spd - p.first;

			tmp2 += snk_spd;
		}

		tmp1++;
		src_tm = p.first;
		global_queue.pop();
	}

	cout << "\nThe average delay of the sources:\n";
	cout << "\nSource\t:\tAverage Delay\n";

	for (i = 0; i < numSource; i++)
	{
		cout << i << "\t:\t" << arr2[i] / arr[i] << "\n";
	}
}

int main()
{
	int numSource, i, j, a;
	double stime;

	cout << "Number of sources: ";
	cin >> numSource;
	source src[numSource];

	int arr[numSource];
	memset(arr, 0, sizeof(arr));

	double arr2[numSource];

	for (i = 0; i < numSource; i++)
		arr2[i] = 0.0;

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
	int tmp1;
	double snk_spd = (double)pkt / (double)sink_wid;

	for (i = 0; i < numSource; i++)
	{
		int k = stime * (double)src[i].sending_rate;
		double src_spd = (double)pkt / (double)src[i].bandwidth;
		double tmp2 = 0.0;
		double k1 = 1 / src[i].sending_rate;
		arr[i] = k;

		for (tmp1 = 0; tmp1 < k; tmp1++)
		{
			if (tmp1 == 0)
			{
				global_queue.push(make_pair(src_spd + k1, i));
				tmp2 = src_spd + k1;
				arr2[i] += src_spd;
			}
			else
			{
				if (k1 * (double)(tmp1) > tmp2)
					tmp2 = k1 * (double)(tmp1);
				else
					arr2[i] += tmp2 - (double)(tmp1) * (double)k1;
				global_queue.push(make_pair(tmp2 + src_spd, i));
				tmp2 += src_spd;
				arr2[i] += src_spd;
			}
		}
	}

	cal(arr2, numSource, snk_spd, arr);

	return 0;
}
