// Name: Anurag
// Roll no: 1601CS05

#include <bits/stdc++.h>
using namespace std;

priority_queue<pair<pair<double, double>, int>, vector<pair<pair<double, double>, int>>, greater<pair<pair<double, double>, int>>> global_queue;

class source
{
  public:
	double sending_rate;
	int bandwidth;
};

double cal(double rt, double r1)
{
	double r2 = (-1 / rt) * (log(1 - r1));
	return r2;
}

bool compair(const pair<double, pair<double, int>> &pair1, const double v)
{
	if (pair1.first > v)
		return false;
	else
		return true;
}

int main()
{
	int num = 3;
	vector<double> vec1;
	vector<double> vec2;
	vector<double> vec3;

	double tm;
	int i, sink_wid, packet;
	cout<<"Sources: 3\n";
	cout<<"Enter bandwidth of each source: \n";
	source tmp[num + 1];

	for (i = 1; i <= num; i++)
	{
		int y1;
		cin>>y1;
		tmp[i].bandwidth = y1;
	}

	cout << "Enter bandwidth of sink: ";
	cin >> sink_wid;
	cout << "Enter packet size ";
	cin >> packet;
	cout << "Enter simulation time:\n";
	cin >> tm;

	double a;

	for (a = 0.0; a <= 20; a = a + 0.5)
	{
		double b;
		b = (double)a;
		tmp[1].sending_rate = b;
		tmp[2].sending_rate = b + 0.5;
		tmp[3].sending_rate = b + 1;

		int count[num + 1];
		double sum[num + 1];

		for (i = 1; i <= num; i++)
			sum[i] = 0.0;

		memset(count, 0, sizeof(count));

		int j = 1;
		int packet_loss[num + 1];

		memset(packet_loss, 0, sizeof(count));

		double snk_spd = ((double)packet) / ((double)sink_wid);
		for (i = 1; i <= num; i++)
		{
			double sp = ((double)packet) / ((double)tmp[i].bandwidth);
			double d = 0.0;
			double tmp1 = 0.0;
			srand((long)time(NULL));

			for (; d < tm;)
			{
				if (d == 0.0)
				{
					global_queue.push(make_pair(make_pair(sp, sp), i));
					d = sp;
					sum[i] += sp;
					count[i]++;
				}
				else
				{
					pair<pair<double, double>, int> p1 = global_queue.top();
					if (d < tmp1)
					{
						d = tmp1;
						global_queue.push(make_pair(make_pair(d + sp, sp), i));
					}
					else
					{
						sum[i] += abs(d - tmp1);
						global_queue.push(make_pair(make_pair(d + sp, sp + d - tmp1), i));
					}
					sum[i] += sp;
					d += sp;
					count[i]++;
				}

				double r1 = rand() / (double)RAND_MAX;
				tmp1 += cal(tmp[i].sending_rate, r1);
			}
		}

		double d = 0.0;
		j = 1;
		int sz = 100;

		double tmp_tm = 0.0;
		vector<pair<double, pair<double, int>>> vec_ans;

		while (!global_queue.empty())
		{
			pair<pair<double, double>, int> p1 = global_queue.top();
			if (j == 1)
			{
				if (p1.first.first + snk_spd <= tm)
				{
					sum[p1.second] += snk_spd;
					vec_ans.push_back(make_pair(p1.first.first, make_pair(p1.first.first, p1.second)));
				}
				else
				{
					sum[p1.second] -= p1.first.second;
					count[p1.second]--;
				}
				d = snk_spd + p1.first.first;
			}
			else
			{
				if (p1.first.first >= d)
				{
					if (p1.first.first + snk_spd <= tm)
					{
						sum[p1.second] += snk_spd;
						vec_ans.push_back(make_pair(p1.first.first, make_pair(p1.first.first, p1.second)));
					}
					else
					{
						sum[p1.second] -= p1.first.second;
						count[p1.second]--;
					}
					d = p1.first.first;
				}
				else
				{
					if (p1.first.first + snk_spd + abs(d - p1.first.first) <= tm)
					{
						sum[p1.second] += snk_spd + abs(d - p1.first.first);
						vec_ans.push_back(make_pair(d, make_pair(p1.first.first, p1.second)));
					}
					else
					{
						sum[p1.second] -= p1.first.second;
						count[p1.second]--;
					}
				}
				d += snk_spd;
			}
			tmp_tm = p1.first.first;
			j++;
			global_queue.pop();
		}

		for (i = sz; i < vec_ans.size(); i++)
		{
			if (lower_bound(vec_ans.begin(), vec_ans.end(), vec_ans[i].second.first, compair) != vec_ans.end())
			{
				int j = lower_bound(vec_ans.begin(), vec_ans.end(), vec_ans[i].second.first, compair) - vec_ans.begin();
				if (abs(j - i) > sz)
					packet_loss[vec_ans[i].second.second]++;
			}
		}

		for (i = 1; i <= num; i++)
		{
			if (i == 1)
			{
				if (count[i] == 0)
					vec1.push_back((double)0);
				else
					vec1.push_back(packet_loss[i] / (double)count[i]);
			}
			else if (i == 2)
			{
				if (count[i] == 0)
					vec2.push_back((double)0);
				else
					vec2.push_back(packet_loss[i] / (double)count[i]);
			}
			else
			{
				if (count[i] == 0)
					vec3.push_back((double)0);
				else
					vec3.push_back(packet_loss[i] / (double)count[i]);
			}
		}
	}

	cout<<"The average delay of the sources are:\n";

	cout << "Source 1\n";
	for (i = 0; i < vec1.size(); i++)
		cout << vec1[i] << "\n";

	cout << "Source 2\n";
	for (i = 0; i < vec2.size(); i++)
		cout << vec2[i] << "\n";

	cout << "Source 3\n";
	for (i = 0; i < vec3.size(); i++)
		cout << vec3[i] << "\n";

	return 0;
}
