#ifndef _INT_STORAGE_
#define _INT_STORAGE_

#include <string>

#include "NEFrame/NodesEditor/Nodes/Node/Node.hpp"


class IntStorage : public Node {
public:
	static inline std::string CLASS_NAME = "Int storage";

private:
	intptr value;

public:
	IntStorage();

	intptr getInt() override;
};

#endif // _INT_STORAGE_

