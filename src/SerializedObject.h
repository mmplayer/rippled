#ifndef __SERIALIZEDOBJECT__
#define __SERIALIZEDOBJECT__

#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "SerializedTypes.h"

enum SOE_Type
{
	SOE_NEVER=-1, SOE_REQUIRED=0, SOE_FLAGS, SOE_IFFLAG=1, SOE_IFNFLAG=2
};

struct SOElement
{ // An element in the description of a serialized object
	const char *e_name;
	SerializedTypeID e_id;
	SOE_Type e_type;
	int e_flags;
};

class STUObject : public SerializedType
{
protected:
	boost::ptr_vector<SerializedType> data;
	std::vector<SOElement*> type;

public:
	STUObject(const char *n=NULL) : SerializedType(n) { ; }
	STUObject(SOElement *t, const char *n=NULL);
	STUObject(SOElement *t, SerializerIterator& u, const char *n=NULL);
	virtual ~STUObject() { ; }

	int getLength() const;
	SerializedTypeID getType() const { return STI_OBJECT; }
	STUObject* duplicate() const { return new STUObject(*this); }

	void add(Serializer& s) const;
	std::string getFullText() const;
	std::string getText() const;

	void addObject(const SerializedType& t) { data.push_back(t.duplicate()); }
	void giveObject(SerializedType* t) { data.push_back(t); }
	const boost::ptr_vector<SerializedType>& peekData() const { return data; }
	boost::ptr_vector<SerializedType>& peekData() { return data; }

	int getCount() const { return data.size(); }
	const SerializedType& peekAt(int offset) const { return data[offset]; }
	SerializedType& getAt(int offset) { return data[offset]; }
};


#endif
