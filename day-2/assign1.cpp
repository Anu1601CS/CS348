// Name: Anurag
// Roll no: 1601CS05

#include <bits/stdc++.h>
using namespace std;

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
	if (pair1.first < v)
		return true;
	else
		return false;
}

priority_queue<pair<pair<double, double>, int>, vector<pair<pair<double, double>, int>>, greater<pair<pair<double, double>, int>>> global_queue;

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
			double x2 = 0.0;
			double tm1 = 0.0;
			srand((long)time(NULL));

			for (; x2 < tm;)
			{
				if (x2 == 0.0)
				{
					global_queue.push(make_pair(make_pair(sp, sp), i));
					x2 = sp;
					sum[i] += sp;
					count[i]++;
				}
				else
				{
					pair<pair<double, double>, int> p1 = global_queue.top();
					if (x2 < tm1)
					{
						x2 = tm1;
						global_queue.push(make_pair(make_pair(x2 + sp, sp), i));
					}
					else
					{
						sum[i] += (abs(x2 - tm1));
						global_queue.push(make_pair(make_pair(x2 + sp, sp + x2 - tm1), i));
					}
					sum[i] += sp;
					x2 += sp;
					count[i]++;
				}

				double r1 = rand() / (double)RAND_MAX;
				tm1 += cal(tmp[i].sending_rate, r1);
			}
		}

		double x2 = 0.0;
		j = 1;
		int sz = 100;

		double tmp_tm = 0.0;
		vector<pair<double, pair<double, int>>> v_ans;

		while (!global_queue.empty())
		{
			pair<pair<double, double>, int> p1 = global_queue.top();
			if (j == 1)
			{
				if (p1.first.first + snk_spd <= tm)
				{
					sum[p1.second] += (snk_spd);
					v_ans.push_back(make_pair(p1.first.first, make_pair(p1.first.first, p1.second)));
				}
				else
				{
					sum[p1.second] -= p1.first.second;
					count[p1.second]--;
				}
				x2 = (snk_spd) + p1.first.first;
			}
			else
			{
				if (p1.first.first >= x2)
				{
					if (p1.first.first + snk_spd <= tm)
					{
						sum[p1.second] += (snk_spd);
						v_ans.push_back(make_pair(p1.first.first, make_pair(p1.first.first, p1.second)));
					}
					else
					{
						sum[p1.second] -= p1.first.second;
						count[p1.second]--;
					}
					x2 = p1.first.first;
				}
				else
				{
					if (p1.first.first + snk_spd + abs(x2 - p1.first.first) <= tm)
					{
						sum[p1.second] += (snk_spd) + abs(x2 - p1.first.first);
						v_ans.push_back(make_pair(x2, make_pair(p1.first.first, p1.second)));
					}
					else
					{
						sum[p1.second] -= p1.first.second;
						count[p1.second]--;
					}
				}
				x2 += snk_spd;
			}
			tmp_tm = p1.first.first;
			j++;
			global_queue.pop();
		}

		for (i = sz; i < v_ans.size(); i++)
		{
			if (lower_bound(v_ans.begin(), v_ans.end(), v_ans[i].second.first, compair) != v_ans.end())
			{
				int j = lower_bound(v_ans.begin(), v_ans.end(), v_ans[i].second.first, compair) - v_ans.begin();
				if (abs(j - i) > sz)
					packet_loss[v_ans[i].second.second]++;
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

	printf("The average delay of the sources are:\n");
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
