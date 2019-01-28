#include <bits/stdc++.h>
#define SYNC                     \
	ios::sync_with_stdio(false); \
	cin.tie(NULL);               \
	cout.tie(NULL);

using namespace std;
#define mp make_pair
#define pb push_back
typedef pair<pair<double, double>, int> pfi;

class source
{
  public:
	double sending_rate;
	int bandwidth;
};

double func(double rt, double r1)
{
	double r2 = (-1 / rt) * (log(1 - r1));
	return r2;
}

bool cmp2(const pair<double, pair<double, int>> &p1, const double v)
{
	if (p1.first < v)
		return true;
	else
		return false;
}

int main()
{
	SYNC int num = 3;
	vector<double> vec1;
	vector<double> vec2;
	vector<double> vec3;

	double tm;
	printf("Sources: 3\n");
	printf("Enter bandwidth of each source: \n");
	source tmp[num + 1];
	int i = 1;

	for (i = 1; i <= num; i++)
	{
		int y1;
		scanf("%d", &y1);
		tmp[i].bandwidth = y1;
	}

	printf("Enter bandwidth of sink: ");
	int x1_1;
	scanf("%d", &x1_1);
	int sink_wid = x1_1;
	printf("Enter packet size ");
	int pkt;
	scanf("%d", &pkt);
	printf("Enter simulation time:\n");
	scanf("%lf", &tm);
	double k1 = 0.0;

	priority_queue<pfi, vector<pfi>, greater<pfi>> pq;

	for (; k1 <= 20; k1 = k1 + 0.5)
	{
		double x1;
		x1 = (double)k1;
		tmp[1].sending_rate = x1;
		tmp[2].sending_rate = x1 + 0.5;
		tmp[3].sending_rate = x1 + 1;

		int cnt[num + 1];
		double sum[num + 1];

		for (i = 1; i <= num; i++)
			sum[i] = 0.0;

		memset(cnt, 0, sizeof(cnt));

		int j = 1;
		int packet_loss[num + 1];

		memset(packet_loss, 0, sizeof(cnt));

		double snk_sp = ((double)pkt) / ((double)sink_wid);
		for (i = 1; i <= num; i++)
		{
			double sp = ((double)pkt) / ((double)tmp[i].bandwidth);
			double x2 = 0.0;
			double tm1 = 0.0;
			srand((long)time(NULL));

			for (; x2 < tm;)
			{
				if (x2 == 0.0)
				{
					pq.push(mp(mp(sp, sp), i));
					x2 = sp;
					sum[i] += sp;
					cnt[i]++;
				}
				else
				{
					pfi p1 = pq.top();
					if (x2 < tm1)
					{
						x2 = tm1;
						pq.push(mp(mp(x2 + sp, sp), i));
					}
					else
					{
						sum[i] += (abs(x2 - tm1));
						pq.push(mp(mp(x2 + sp, sp + x2 - tm1), i));
					}
					sum[i] += sp;
					x2 += sp;
					cnt[i]++;
				}

				double r1 = rand() / (double)RAND_MAX;
				tm1 += func(tmp[i].sending_rate, r1);
			}
		}

		double x2 = 0.0;
		j = 1;
		int sz = 100;

		double tmp_tm = 0.0;
		vector<pair<double, pair<double, int>>> v_ans;

		while (!pq.empty())
		{
			pfi p1 = pq.top();
			if (j == 1)
			{
				if (p1.first.first + snk_sp <= tm)
				{
					sum[p1.second] += (snk_sp);
					v_ans.pb(mp(p1.first.first, mp(p1.first.first, p1.second)));
				}
				else
				{
					sum[p1.second] -= p1.first.second;
					cnt[p1.second]--;
				}
				x2 = (snk_sp) + p1.first.first;
			}
			else
			{
				if (p1.first.first >= x2)
				{
					if (p1.first.first + snk_sp <= tm)
					{
						sum[p1.second] += (snk_sp);
						v_ans.pb(mp(p1.first.first, mp(p1.first.first, p1.second)));
					}
					else
					{
						sum[p1.second] -= p1.first.second;
						cnt[p1.second]--;
					}
					x2 = p1.first.first;
				}
				else
				{
					if (p1.first.first + snk_sp + abs(x2 - p1.first.first) <= tm)
					{
						sum[p1.second] += (snk_sp) + abs(x2 - p1.first.first);
						v_ans.pb(mp(x2, mp(p1.first.first, p1.second)));
					}
					else
					{
						sum[p1.second] -= p1.first.second;
						cnt[p1.second]--;
					}
				}
				x2 += snk_sp;
			}
			tmp_tm = p1.first.first;
			j++;
			pq.pop();
		}

		for (i = sz; i < v_ans.size(); i++)
		{
			if (lower_bound(v_ans.begin(), v_ans.end(), v_ans[i].second.first, cmp2) != v_ans.end())
			{
				int j = lower_bound(v_ans.begin(), v_ans.end(), v_ans[i].second.first, cmp2) - v_ans.begin();
				if (abs(j - i) > sz)
					packet_loss[v_ans[i].second.second]++;
			}
		}

		for (i = 1; i <= num; i++)
		{
			if (i == 1)
			{
				if (cnt[i] == 0)
					vec1.push_back((double)0);
				else
					vec1.push_back(packet_loss[i] / (double)cnt[i]);
			}
			else if (i == 2)
			{
				if (cnt[i] == 0)
					vec2.push_back((double)0);
				else
					vec2.push_back(packet_loss[i] / (double)cnt[i]);
			}
			else
			{
				if (cnt[i] == 0)
					vec3.push_back((double)0);
				else
					vec3.push_back(packet_loss[i] / (double)cnt[i]);
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
