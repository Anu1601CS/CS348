#include <bits/stdc++.h>
#define SYNC                     \
	ios::sync_with_stdio(false); \
	cin.tie(NULL);               \
	cout.tie(NULL);

using namespace std;
typedef pair<double, int> pdi;

struct src
{
	double sending_rate;
	int bandwidth;
};

int main()
{
	SYNC int num;
	double tm;
	cout<<"Enter the number of sources: ";
	cin>>num;
	cout<<"Enter sending rate(pkt/sec) and bandwidth(in bits) of each source: \n";
	struct src tmp[num + 1];
	int i = 1;
	int cnt[num + 1];
	double sum[num + 1];

	for (i = 1; i <= num; i++)
		sum[i] = 0.0;
	memset(cnt, 0, sizeof(cnt));

	for (i = 1; i <= num; i++)
	{
		double x1;
		int y1;
		scanf("%lf%d", &x1, &y1);
		tmp[i].sending_rate = x1;
		tmp[i].bandwidth = y1;
	}

	cout<<"Enter bandwidth of sink: ";
	int x1;
	cin>>x1;
	int sink_wid = x1;
	cout<<"Enter packet size(in bits): ";
	int pkt;
	cin>>pkt;
	cout<<"Enter simulation time(in sec):\n";
	cin>>tm;

	priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
	int j = 1;
	double snk_sp = ((double)pkt) / ((double)sink_wid);

	for (i = 1; i <= num; i++)
	{
		int k = tm * (double)tmp[i].sending_rate;
		double sp = ((double)pkt) / ((double)tmp[i].bandwidth);
		double x2 = 0.0;
		double k1 = 1 / (tmp[i].sending_rate);
		cnt[i] = k;

		for (j = 1; j <= k; j++)
		{
			if (j == 1)
			{
				pq.push(make_pair(sp + k1, i));
				x2 = sp + k1;
				sum[i] += sp;
			}
			else
			{
				if (x2 < (double)(j)*k1)
					x2 = (double)(j)*k1;
				else
					sum[i] += (abs(x2 - (double)(j) * (double)k1));
				pq.push(make_pair(x2 + sp, i));
				sum[i] += sp;
				x2 += sp;
			}
		}
	}

	double x2 = 0.0;
	j = 1;
	double tmp_tm = 0.0;

	while (!pq.empty())
	{
		pdi p1 = pq.top();

		if (j == 1)
		{
			sum[p1.second] += (snk_sp);
			x2 = (snk_sp) + p1.first;
		}
		else
		{
			if (p1.first >= x2)
			{
				sum[p1.second] += (snk_sp);
				x2 = p1.first;
			}
			else
			{
				sum[p1.second] += (snk_sp + abs(x2 - p1.first));
			}

			x2 += snk_sp;
		}

		tmp_tm = p1.first;
		j++;
		pq.pop();
	}

	cout<<"The average delay of the sources are (1 to n):\n";

	for (i = 1; i <= num; i++)
	{
		cout << i << ": " << sum[i] / cnt[i] << "\n";
	}
	return 0;
}
