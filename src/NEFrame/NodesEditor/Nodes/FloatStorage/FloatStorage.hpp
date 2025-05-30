#ifndef _FLOAT_STORAGE_
#define _FLOAT_STORAGE_

#include <string>

#include "NEFrame/NodesEditor/Nodes/Node/Node.hpp"


class FloatStorage : public Node {
public:
	static inline std::string CLASS_NAME = "Float storage";

private:
	std::shared_ptr<float> value;

public:
	FloatStorage();

	std::shared_ptr<float> getFloat() override;
};

#endif // _FLOAT_STORAGE_