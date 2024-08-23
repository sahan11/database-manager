#include "rdb-basics.cpp"
#include <bits/stdc++.h>
Basics B;
Relation *naturaljoin(Relation *_R1, Relation *_R2, list<string> joinattr)
{
    Relation *res;
    Relation *R1 = new Relation(*_R1);
    Relation *R2 = new Relation(*_R2);
    // find common attributes and their indices in respective relations
    map<string, int> R1_index;
    map<string, int> R2_index;
    map<string, int> R1_cnt;
    map<string, int> R2_cnt;
    vector<string> common_attributes;
    for (int i = 0; i < R1->natttr; ++i)
    {
        R1_index[R1->attrnames[i]] = i;
        R1_cnt[R1->attrnames[i]]++;
    }
    for (int i = 0; i < R2->natttr; ++i)
    {
        R2_index[R2->attrnames[i]] = i;
        R2_cnt[R2->attrnames[i]]++;
    }
    for (auto it = R2->attrnames.begin(); it != R2->attrnames.end(); ++it)
    {
        // reversing the common attribute names
        if (R1_cnt[*it] != 0)
        {
            common_attributes.push_back(*it);
            reverse(it->begin(), it->end());
        }
    }

    // construct DNFformula and filter res accordingly
    DNFformula *f = new DNFformula;
    res = B._cartesianproduct(R1, R2);
    for (auto it1 : R1->recs)
    {
        for (auto it2 : R2->recs)
        {
            list<tuple<string, char, Attr *>> temp;
            bool x1 = true;
            for (auto i : common_attributes)
            {

                if (*it1->attrptr[R1_index[i]] == *it2->attrptr[R2_index[i]])
                {
                    temp.push_back(make_tuple(i, '=', it1->attrptr[R1_index[i]]));
                    string s = i;
                    reverse(s.begin(), s.end());
                    temp.push_back(make_tuple(s, '=', it1->attrptr[R1_index[i]]));
                }
                else
                {
                    x1 = false;
                    break;
                }
            }
            if (x1)
            {
                f->ops.push_back(temp);
            }
        }
    }
    res = B._selection(res, f);

    // remove the reversed colomn
    list<string> selection;
    for (auto it : res->attrnames)
    {
        bool x = true;
        for (auto it2 : common_attributes)
        {
            string s = it2;
            reverse(s.begin(), s.end());
            if (it == s)
            {
                x = false;
                break;
            }
        }
        if (x)
        {
            selection.push_back(it);
        }
    }
    res = B._projection(res, selection);
    return res;
}