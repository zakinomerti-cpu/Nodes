#ifndef _NODES_DB_
#define _NODES_DB_

#include <list>
#include <memory>
#include <functional>
#include <unordered_map>
#include <exception>

#include "NEFrame/NodesEditor/Nodes/Node/Node.hpp"
#include "NEFrame/Formating/LinkInfo.hpp"

typedef std::shared_ptr<Node> nodeptr;
typedef std::shared_ptr<LinkInfo> liptr;

typedef std::list<nodeptr> nlist;
typedef std::list<liptr> lilist;

typedef std::list<lilist::iterator> l2ilist;

typedef std::unordered_map<uint, l2ilist> grh;
typedef std::unordered_map<uint, nlist::iterator> nmap;
typedef std::unordered_map<uint, lilist::iterator> limap;

typedef std::function<void(Node*)> onf;
typedef std::function<void(LinkInfo*)> olif;

typedef std::list<std::pair<nodeptr, uint>> nplist;
typedef std::pair<nodeptr, nodeptr> nodepair;

class NodesDB {
private:
	uint lastLinkID = 0;

	nlist nodes;
	lilist links;

	nmap nodesMap;
	grh graph;
	limap linkInfoMap;

public:
	void doOverNodes(std::function<void(Node*)> func);
	void doOverLinks(std::function<void(LinkInfo*)> func);

	nodeptr getNode(uint nodeID);
	liptr getLinkInfo(uint linkID);

	void delNode(uint nodeID);

	void delLinkByLinkID(uint linkID);
	void delLinkByNodeID(uint nodeID);

	nodeptr getSender(uint outPointID);
	nodeptr getRecipient(uint inPointID);

	void getRecipients(nplist& recipients, uint nodeOutID);

	void addLink(
		uint nodeOutID,
		uint outPointID,
		uint nodeInID,
		uint inPointID
	);

	void addNode(nodeptr node);
};

#endif // _NODES_DB_
