#include "rdb-attr.cpp"
#include <algorithm>
#include <bits/stdc++.h>
bool Basics::_is_valid(Relation *R1, Relation *R2)
{
    // Check if the schemas are same
    if (R1->natttr != R2->natttr)
    {
        cout << "Different Numeber of attributes!" << endl;
        // Relation* temp = new Relation();
        return false;
    }
    R1->create_attr_pair_type();
    R2->create_attr_pair_type();
    sort(R1->attr_pair_type.begin(), R1->attr_pair_type.end());
    sort(R2->attr_pair_type.begin(), R2->attr_pair_type.end());
    for (int i = 0; i < R1->natttr; i++)
    {
        if (R1->attr_pair_type[i] != R2->attr_pair_type[i])
        {
            cout << "Different Attributes!" << endl;
            // Relation* temp = new Relation();
            return false;
        }
    }
    return true;
}
// 1. Union: All records of both R1 and R2.
// Relation * union(Relation * R1, Relation * R2)
Relation *Basics::_union(Relation *R1, Relation *R2)
{
    if (!_is_valid(R1, R2))
    {
        return NULL;
    }
    Relation *R3 = new Relation(*R1);
    // R3->relation_print();
    cout << endl;
    R3->nrecs += R2->nrecs;
    // adding the records of Relation R2 with the attributes in same order as in R1
    for (auto it = R2->recs.begin(); it != R2->recs.end(); it++)
    {
        // creating a new record with entries same as in the Relation 2
        auto temp = new Record(**it);
        // temp->print_record();
        vector<Attr *> temp_vec;
        for (int i = 0; i < R1->natttr; i++)
        {
            temp_vec.push_back(temp->attrptr[i]);
        }
        // changing the order of elements in the record according to the elements in R1
        for (int i = 0; i < R1->natttr; i++)
        {
            int j = 0;
            // here j corresponds to the index of the attribute name at index i (in Relaion 2) in Realtion 1
            if (R2->attrnames[i] != R1->attrnames[j])
            {
                j++;
            }
            temp->attrptr[R1->attrinds[j]] = temp_vec[i];
        }
        // Removing common entries
        int flag = 1;
        for (auto it = R1->recs.begin(); it != R1->recs.end(); it++)
        {
            int count = 0;
            for (int i = 0; i < R1->natttr; i++)
            {
                // ((*it)->attrptr[i])->print();
                // cout << "";
                // temp->attrptr[i]->print();
                // cout << "\t";
                // counting the number of common recored entries
                if (*((*it)->attrptr[i]) == *(temp->attrptr[i]))
                {
                    count++;
                }
                // cout << count;
                if (count == R1->natttr)
                {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag == 1)
        {
            R3->recs.push_back(temp);
        }
    }
    return R3;
}
// 2. Difference: Records in R1 but not in R2
// Relation * difference (Relation * R1, Relation * R2)
Relation *Basics::_difference(Relation *R1, Relation *R2)
{
    Relation *R = new Relation(R1->natttr, R1->attrnames, R1->attrinds, R1->attribute_type);
    int flag = 0;
    if (!_is_valid(R1, R2))
    {
        return NULL;
    }
    // for each record in R1 check if it is available in R2; if not then create a new copy record of R1 and append it in the new Relation that is being returned
    // auto temp = new Record(R2);

    for (auto it = R1->recs.begin(); it != R1->recs.end(); it++)
    {
        // creating a new record with entries same as in the Relation 2
        auto temp = new Record(**it);
        // temp->print_record();
        vector<Attr *> temp_vec;
        for (int i = 0; i < R1->natttr; i++)
        {
            temp_vec.push_back(temp->attrptr[i]);
        }
        // changing the order of elements in the record according to the elements in R1
        for (int i = 0; i < R1->natttr; i++)
        {
            int j = 0;
            // here j corresponds to the index of the attribute name at index i (in Relaion 2) in Realtion 1
            if (R1->attrnames[i] != R2->attrnames[j])
            {
                j++;
            }
            temp->attrptr[R2->attrinds[j]] = temp_vec[i];
        }
        // Removing common entries
        int flag = 1;
        for (auto it = R2->recs.begin(); it != R2->recs.end(); it++)
        {
            int count = 0;
            for (int i = 0; i < R1->natttr; i++)
            {
                // ((*it)->attrptr[i])->print();
                // cout << "";
                // temp->attrptr[i]->print();
                // cout << "\t";
                // counting the number of common recored entries
                if (*((*it)->attrptr[i]) == *(temp->attrptr[i]))
                {
                    count++;
                }
                // cout << count;
                if (count == R1->natttr)
                {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag == 1)
        {
            R->recs.push_back(*it);
        }
    }
    return R;
}
// 3. Cartesian Product: All possible pairs of records from R1 and R2
Relation *Basics::_cartesianproduct(Relation *R1, Relation *R2)
{
    // you need to create a new table with attributes of both the Relations and the record contains the values of records of both the tables
    // checking for cartition product only when attributes names are different
    for (int i = 0; i < R1->natttr; i++)
    {
        for (int j = 0; j < R2->natttr; j++)
        {
            if (R1->attrnames[i] == R2->attrnames[j])
            {
                cout << "Attributes names are same. Cannot perform cartesian product." << endl;
                return NULL;
            }
        }
    }

    vector<string> temp_names = R1->attrnames;
    vector<int> temp_idx = R1->attrinds;
    vector<int> temp_type = R1->attribute_type;
    for (int i = 0; i < R2->natttr; i++)
    {
        temp_names.push_back(R2->attrnames[i]);
        temp_idx.push_back(R2->attrinds[i] + R1->natttr);
        temp_type.push_back(R2->attribute_type[i]);
    }
    Relation *R3 = new Relation(R1->natttr + R2->natttr, temp_names, temp_idx, temp_type);
    for (auto it = R1->recs.begin(); it != R1->recs.end(); it++)
    {

        for (auto iit = R2->recs.begin(); iit != R2->recs.end(); iit++)
        {
            Record *temp_R1 = new Record(**it);
            Record *temp_R2 = new Record(**iit);
            for (int i = 0; i < R2->natttr; i++)
            {
                temp_R1->attrptr.push_back(temp_R2->attrptr[i]);
            }
            R3->recs.push_back(temp_R1);
        }
    }
    return R3;
}
// 4. Projection: New relation with a subset of columns
Relation *Basics::_projection(Relation *R1, list<string> projectattrs)
{
    // you need to make a new reltion with attribute only present in the list provided in the paramater
    //  you can create a new map of list attr_names and their index there after for creating a new record just add the elements
    map<string, int> name_map_idx, name_map_type;
    for (int i = 0; i < R1->natttr; i++)
    {
        name_map_idx[R1->attrnames[i]] = R1->attrinds[i];
        name_map_type[R1->attrnames[i]] = R1->attribute_type[i];
    }
    vector<int> temp_type, temp_idx;
    vector<string> temp_attributes;
    int i = 0;
    for (auto str : projectattrs)
    {
        temp_attributes.push_back(str);
        temp_type.push_back(name_map_type[str]);
        temp_idx.push_back(i++);
    }
    // increase the number of records in the Relation each time you add the record
    Relation *R2 = new Relation(projectattrs.size(), temp_attributes, temp_idx, temp_type);
    for (auto _rec : R1->recs)
    {
        R2->nrecs++;
        Record *temp_rec = new Record;
        for (auto str : temp_attributes)
        {
            temp_rec->attrptr.push_back((*_rec).attrptr[name_map_idx[str]]->copy_attr());
        }
        R2->recs.push_back(temp_rec);
    }
    return R2;
}
// 5. Selection: New relation with a subset of records matching a boolean expression in the attribute values in disjunctive normal form.
Relation *Basics::_selection(Relation *R1, DNFformula *f)
{
    // you are given a comparator that has string - Attribute name, char - boolean operator and Attr* pointer to a constant Attribute
    // you need to create a new table of the records that satisfy this comparator
    //  a record will only satisfy one of the three boolean operation
    //  basically the dnf form is a list of list of comparators and a record should staisfy one or more of these list of a comparator and should satisfy all of these comparators
    Relation *R2 = new Relation(R1->natttr, R1->attrnames, R1->attrinds, R1->attribute_type);
    map<string, int> name_map_idx, name_map_type;
    for (int i = 0; i < R1->natttr; i++)
    {
        name_map_idx[R1->attrnames[i]] = R1->attrinds[i];
        name_map_type[R1->attrnames[i]] = R1->attribute_type[i];
    }
    for (auto it : R1->recs)
    {
        // variable to check whether to add or not a record in new Relation
        int flag = 0;
        for (list<tuple<string, char, Attr *>> dis_comparator : f->ops)
        {
            int count = 0;
            for (tuple<string, char, Attr *> con_comparator : dis_comparator)
            {
                // name_map_idx[get<0>(con_comparator)]; gives you the index of the attribute in the string
                auto idx = name_map_idx.find(get<0>(con_comparator));
                // checking if the attribute is present in the record or not
                if (idx != name_map_idx.end())
                {
                    // if present then check for the boolean operator and the value of the attribute
                    int i = name_map_idx[get<0>(con_comparator)];
                    // get<1>(con_comparator) gives you the boolean operator
                    char _operator = get<1>(con_comparator);
                    // get<2>(con_comparator) gives you the pointer to the constant attribute
                    Attr *value = get<2>(con_comparator);
                    // it->attrptr[i] gives you the pointer to the attribute in the record
                    Attr *element = it->attrptr[i];
                    // element->print();
                    // value->print();
                    if (_operator == '<')
                    {
                        if (*element < *value)
                        {
                            // cout << "smaller \t " << endl;
                            count++;
                        }
                    }
                    if (_operator == '>')
                    {
                        if (*element > *value)
                        {
                            // cout << "greator \t " << endl;
                            count++;
                        }
                    }
                    if (_operator == '=')
                    {
                        if ((*element == *value))
                        {
                            // cout << "equal\t " << endl;
                            count++;
                        }
                    }
                }
            }
            if (count == dis_comparator.size())
            {
                // indication to include this record in new Relation
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            R2->nrecs++;
            R2->recs.push_back(new Record(*it));
        }
    }
    return R2;
}
// 6. Rename: rename an attribute in schema
Relation *Basics::_rename(Relation *R, const string &s1, const string &s2)
{
    int i = 0;
    for (i = 0; i < R->natttr; i++)
    {
        if (R->attrnames[i] == s1)
        {
            R->attrnames[i] = s2;
            break;
        }
    }
    if (i == R->natttr)
    {
        cout << "NO such Attribute with the name \" " << s1 << " \" found!" << endl;
    }
    return R;
}
// 7. Natural Join: join two relations on the common attributes
Relation *naturaljoin(Relation *_R1, Relation *_R2, list<string> joinattr)
{
    Basics B;
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
