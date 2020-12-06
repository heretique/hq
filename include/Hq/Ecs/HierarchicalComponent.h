#pragma once

#include "entt/fwd.hpp"
#include "entt/entity/entity.hpp"
#include "entt/entity/registry.hpp"

#include <queue>

namespace hq
{
template <typename T>
struct HierarchicalComponent
{
    entt::entity parent {entt::null};
    entt::entity firstChild {entt::null};
    entt::entity prevSibling {entt::null};
    entt::entity nextSibling {entt::null};

    template <class Serializer>
    void Serialize(Serializer& serializer)
    {
        SERIALIZE(parent);
        SERIALIZE(firstChild);
        SERIALIZE(prevSibling);
        SERIALIZE(nextSibling);
    }
};

template <typename HierarchicalComp, typename VisitorF>
void VisitHierarchyDepthFirst(entt::registry& registry, entt::entity entity, VisitorF& visitor)
{
    visitor(registry, entity);
    assert(registry.has<HierarchicalComp>(entity));
    const HierarchicalComp& component = registry.get<HierarchicalComp>(entity);
    HierarchicalComp*       childComp = nullptr;
    entt::entity            nextChild = component.firstChild;
    if (nextChild != entt::null)
    {
        do
        {
            VisitHierarchyDepthFirst<HierarchicalComp, VisitorF>(registry, nextChild, visitor);
            childComp = registry.try_get<HierarchicalComp>(nextChild);
        } while (childComp && ((nextChild = childComp->nextSibling) != entt::null));
    }
}

template <typename HierarchicalComp, typename VisitorF>
void VisitHierarchyDepthFirstPost(entt::registry& registry, entt::entity entity, VisitorF& visitor)
{
    assert(registry.has<HierarchicalComp>(entity));
    const HierarchicalComp& component = registry.get<HierarchicalComp>(entity);
    HierarchicalComp*       childComp = nullptr;
    entt::entity            nextChild = component.firstChild;
    if (nextChild != entt::null)
    {
        do
        {
            VisitHierarchyDepthFirst<HierarchicalComp, VisitorF>(registry, nextChild, visitor);
            childComp = registry.try_get<HierarchicalComp>(nextChild);
        } while (childComp && ((nextChild = childComp->nextSibling) != entt::null));
    }
    visitor(registry, entity);
}

template <typename HierarchicalComp, typename VisitorPredicateF>
void VisitHierarchyDepthFirstWithPredicate(entt::registry& registry, entt::entity entity, VisitorPredicateF& visitor)
{
    if (visitor(registry, entity))
    {
        assert(registry.has<HierarchicalComp>(entity));
        const HierarchicalComp& component = registry.get<HierarchicalComp>(entity);
        HierarchicalComp*       childComp = nullptr;
        entt::entity            nextChild = component.firstChild;
        if (nextChild != entt::null)
        {
            do
            {
                VisitHierarchyDepthFirst<HierarchicalComp, VisitorPredicateF>(registry, nextChild, visitor);
                childComp = registry.try_get<HierarchicalComp>(nextChild);
            } while (childComp && ((nextChild = childComp->nextSibling) != entt::null));
        }
    }
}

template <typename HierarchicalComp, typename VisitorF>
void VisitHierarchyBreadthFirst(entt::registry& registry, entt::entity entity, VisitorF& visitor)
{
    std::queue<entt::entity> queue;
    queue.push(entity);
    entt::entity currentEntity = entt::null;
    while (!queue.empty())
    {
        currentEntity = queue.front();
        queue.pop();
        visitor(registry, currentEntity);
        assert(registry.has<HierarchicalComp>(currentEntity));
        const HierarchicalComp& component = registry.get<HierarchicalComp>(currentEntity);
        HierarchicalComp*       childComp = nullptr;
        entt::entity            nextChild = component.firstChild;
        if (nextChild != entt::null)
        {
            do
            {
                queue.emplace(nextChild);
                childComp = registry.try_get<HierarchicalComp>(nextChild);
            } while (childComp && ((nextChild = childComp->nextSibling) != entt::null));
        }
    }
}

template <typename HierarchicalComp, typename VisitorPredicateF>
void VisitHierarchyBreadthFirstWithPredicate(entt::registry& registry, entt::entity entity, VisitorPredicateF& visitor)
{
    std::queue<entt::entity> queue;
    queue.push(entity);
    entt::entity currentEntity = entt::null;
    while (!queue.empty())
    {
        currentEntity = queue.front();
        queue.pop();
        if (visitor(registry, currentEntity))
        {
            assert(registry.has<HierarchicalComp>(currentEntity));
            const HierarchicalComp& component = registry.get<HierarchicalComp>(currentEntity);
            HierarchicalComp*       childComp = nullptr;
            entt::entity            nextChild = component.firstChild;
            if (nextChild != entt::null)
            {
                do
                {
                    queue.emplace(nextChild);
                    childComp = registry.try_get<HierarchicalComp>(nextChild);
                } while (childComp && ((nextChild = childComp->nextSibling) != entt::null));
            }
        }
    }
}

}
