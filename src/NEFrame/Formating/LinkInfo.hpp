#ifndef _LINKINFO_
#define _LINKINFO_

class LinkInfo {
private:
	unsigned int nodeInID;
	unsigned int inPointID;
	unsigned int nodeOutID;
	unsigned int outPointID;
	unsigned int linkID;

public:
	LinkInfo(
		unsigned int nodeOutID,
		unsigned int outPointID,
		unsigned int nodeInID,
		unsigned int inPointID,
		unsigned int linkID
	);

	unsigned int getInPointID();
	unsigned int getNodeInID();
	unsigned int getOutPointID();
	unsigned int getNodeOutID();
	unsigned int getLinkID();
};

#endif // _LINKINFO_

