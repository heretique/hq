#pragma once

#include <tuple>
#include <variant>
#include <optional>
#include <unordered_map>
#include <cassert>

namespace hq
{
// for each from here: https://www.fluentcpp.com/2019/03/08/stl-algorithms-on-tuples/
template <class Tuple, class F>
constexpr F for_each(Tuple&& t, F&& f)
{
    return for_each_impl(std::forward<Tuple>(t), std::forward<F>(f),
                         std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple> >::value> {});
}

template <class Tuple, class F, std::size_t... I>
constexpr F for_each_impl(Tuple&& t, F&& f, std::index_sequence<I...>)
{
    return (void)std::initializer_list<int> {(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))), 0)...}, f;
}

// index_in_tuple from here: https://stackoverflow.com/questions/18063451/get-index-of-a-tuple-elements-type
template <size_t I, typename T, typename Tuple_t>
constexpr size_t index_in_tuple_fn()
{
    static_assert(I < std::tuple_size<Tuple_t>::value, "The element is not in the tuple");

    typedef typename std::tuple_element<I, Tuple_t>::type el;
    if constexpr (std::is_same<T, el>::value)
    {
        return I;
    }
    else
    {
        return index_in_tuple_fn<I + 1, T, Tuple_t>();
    }
}

template <typename T, typename Tuple_t>
struct index_in_tuple
{
    static constexpr size_t value = index_in_tuple_fn<0, T, Tuple_t>();
};

// got inspiration from here: https://sii.pl/blog/implementing-a-state-machine-in-c17/
template <typename Context, typename TransitionsEnumClass, typename... States>
class FSM
{
public:
    template <typename State>
    void changeState()
    {
        std::optional<TransitionsEnumClass> stateTransition;
        std::visit([this](auto statePtr) { statePtr->onExit(mContext); }, currentState);
        currentState = &std::get<State>(states);
        std::visit([this, &stateTransition](auto statePtr) { stateTransition = statePtr->onEnter(mContext); },
                   currentState);
        if (stateTransition)
        {
            std::cout << "Transition\n";
            changeState(*stateTransition);
        }
    }

    void tick()
    {
        std::optional<TransitionsEnumClass> stateTransition;
        std::visit([this, &stateTransition](auto statePtr) { stateTransition = statePtr->onTick(mContext); },
                   currentState);
        if (stateTransition)
        {
            std::cout << "Transition\n";
            changeState(*stateTransition);
        }
    }

    template <typename State>
    void addTransition(TransitionsEnumClass transition)
    {
        mTransitionToIndex.emplace(std::make_pair(transition, index_in_tuple<State, decltype(states)>::value));
    }

private:
    void changeState(TransitionsEnumClass transition)
    {
        std::optional<TransitionsEnumClass> stateTransition;
        std::visit([this](auto statePtr) { statePtr->onExit(mContext); }, currentState);
        assert(mTransitionToIndex.find(transition) != mTransitionToIndex.end());
        changeState(mTransitionToIndex[transition]);
        std::visit([this, &stateTransition](auto statePtr) { stateTransition = statePtr->onEnter(mContext); },
                   currentState);
        if (stateTransition)
        {
            std::cout << "Transition\n";
            assert(mTransitionToIndex.find(*stateTransition) != mTransitionToIndex.end());
            changeState(mTransitionToIndex[*stateTransition]);
        }
    }

    void changeState(size_t index)
    {
        size_t currentIndex = 0;
        for_each(states, [this, index, &currentIndex](auto&& value) {
            if (currentIndex == index)
            {
                currentState = &value;
            }
            ++currentIndex;
        });
    }

private:
    Context                                          mContext;
    std::tuple<States...>                            states;
    std::variant<States*...>                         currentState {&std::get<0>(states)};
    std::unordered_map<TransitionsEnumClass, size_t> mTransitionToIndex;
};

}  // hq namespace
