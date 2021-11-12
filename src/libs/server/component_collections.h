#pragma once
#include "component.h"
#include "disposable.h"

#include <list>
#include <map>

// ComponentCollections 是按组件类型来存的
class ComponentCollections :public IDisposable
{
public:
    ComponentCollections(std::string componentName);
    ~ComponentCollections();

    void Add(IComponent* pObj);
    void Remove(uint64_t sn);

    IComponent* Get(uint64_t sn = 0);
    std::map<uint64_t, IComponent*>* GetAll();

    void Swap();
    void Dispose() override;

    std::string GetClassType() const;

private:
    std::map<uint64_t, IComponent*> _objs;
    std::map<uint64_t, IComponent*> _addObjs;
    std::list<uint64_t> _removeObjs;

    std::string _componentName{ "" };
};
