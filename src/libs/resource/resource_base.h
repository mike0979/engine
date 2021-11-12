#pragma once

#include <vector>
#include <map>
#include <string>

class ResourceBase
{
public:
	virtual ~ResourceBase() = default;
	explicit ResourceBase(std::map<std::string, int>& head) : _id(0), _head(head) {}

	int GetId() const { return _id; }

	bool LoadProperty(const std::string line);

	// ���ÿ������
	virtual bool Check() = 0;

	static std::vector<std::string> ParserLine(std::string line);

protected:

	// �����ڴ�ṹ
	virtual void GenStruct() = 0;

	std::string GetString(std::string name);
	bool GetBool(std::string name);
	int GetInt(std::string name);

	void DebugHead() const;

private:
	int _id;
	std::map<std::string, int>& _head;
	std::vector<std::string> _props;
};

