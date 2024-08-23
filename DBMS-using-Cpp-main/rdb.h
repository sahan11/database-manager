// #ifndef RDB_H
// #define RDB_H
#include<bits/stdc++.h>

using namespace std;

class Attr;
class Record;
class Relation;
class Basics;

struct DNFformula
{
  list<list<tuple<string, char, Attr *>>> ops;
};

class Attr
{ // Base class for attributes
  // Add operators for different attribute type in derived classes
public:
  virtual bool operator==(const Attr &);
  virtual bool operator!=(const Attr &right);
  virtual bool operator<(const Attr &right);
  virtual bool operator<=(const Attr &right);
  virtual bool operator>(const Attr &right);
  virtual bool operator>=(const Attr &right);
  virtual void print();
  virtual Attr *copy_attr() = 0;
};
class Record
{
  vector<Attr *> attrptr;

public:
  Record(vector<int>&, vector<string>&, int);
  Record(const Record &);
  Record();
  void print_record();
  friend class Relation;
  friend class Basics;
  friend Relation *naturaljoin(Relation *, Relation *, list<string>);
  ~Record();
};
class Relation
{
  int natttr, nrecs;
  vector<string> attrnames;
  vector<int> attrinds;
  list<Record *> recs;

public:
  vector<int> attribute_type;
  vector<pair<string, int>> attr_pair_type;
  map<string, int> name_map_type;
  Relation();
  //constructor for creating a relation
  Relation(int, vector<string>,vector<int>,vector<int>);
  //copy constructor
  Relation(const Relation &);
  void create_attr_pair_type();
  void relation_print();
  void getAttributes();
  void AddRecord();
  friend class Basics;
  friend Relation *naturaljoin(Relation *, Relation *, list<string>);
  ~Relation();
};
class Basics
{
  public:
    bool _is_valid(Relation *, Relation *);
    Relation *_union(Relation *, Relation *);
    Relation *_difference(Relation *, Relation *);
    Relation *_cartesianproduct(Relation *, Relation *);
    Relation *_projection(Relation *, list<string>);
    Relation *_selection(Relation *, DNFformula *);
    Relation *_rename(Relation *, const string &, const string &);
};

class integerAttribute : public Attr
{
    int type;
    int value;

  public:
    integerAttribute(int);
    bool operator==(const Attr &right) const;
    bool operator!=(const Attr &right) const;
    bool operator<(const Attr &right) const;
    bool operator<=(const Attr &right) const;
    bool operator>(const Attr &right) const;
    bool operator>=(const Attr &right) const;
    void print() const;
    int get_value();
    Attr *copy_attr();
};
class stringAttribute : public Attr
{
    int type;
    string value;

  public:
    stringAttribute(string);
    bool operator==(const Attr &right) const;
    bool operator!=(const Attr &right) const;
    bool operator<(const Attr &right) const;
    bool operator<=(const Attr &right) const;
    bool operator>(const Attr &right) const;
    bool operator>=(const Attr &right) const;
    void print() const;
    string get_value();
    Attr *copy_attr();
};
class floatAttribute : public Attr
{
    int type;
    float value;

  public:
    floatAttribute(float);
    bool operator==(const Attr &right) const;
    bool operator!=(const Attr &right) const;
    bool operator<(const Attr &right) const;
    bool operator<=(const Attr &right) const;
    bool operator>(const Attr &right) const;
    bool operator>=(const Attr &right) const;
    void print() const;
    float get_value();
    Attr *copy_attr();
};
class doubleAttribute : public Attr
{
    int type;
    double value;

  public:
    doubleAttribute(double);
    bool operator==(const Attr &right) const;
    bool operator!=(const Attr &right) const;
    bool operator<(const Attr &right) const;
    bool operator<=(const Attr &right) const;
    bool operator>(const Attr &right) const;
    bool operator>=(const Attr &right) const;
    void print() const;
    double get_value();
    Attr *copy_attr();
};
Relation *naturaljoin(Relation *, Relation *, list<string>);

// #endif