#pragma once

#include <cstdint>
#include "Hq/CompileMurmur.h"
#include <unordered_map>

#define SERIALIZE(x) serializer(x, #x)

#define DECLARE_SUPER(X) \
private:                 \
    using super = X;

#define CREATE_TYPEID(x)                             \
public:                                              \
    uint32_t TypeId() override                       \
    {                                                \
        static uint32_t typeId = hq::MURMUR3_32(#x); \
        return typeId;                               \
    }                                                \
                                                     \
private:

namespace hq
{
class Serializer;

class Serializable
{
public:
    virtual ~Serializable() {}
    virtual void     Serialize(Serializer& serializer) = 0;
    virtual uint32_t TypeId()                          = 0;
};

}  // hq namespace

// Serializer registration based on this:
// https://gamedev.stackexchange.com/questions/17746/entity-component-systems-in-c-how-do-i-discover-types-and-construct-component

#define REGISTER_SERIALIZABLE_TYPE(TYPE)                                                                 \
    namespace serializable                                                                               \
    {                                                                                                    \
        namespace detail                                                                                 \
        {                                                                                                \
            namespace                                                                                    \
            {                                                                                            \
                template <class T>                                                                       \
                class SerializableRegistration;                                                          \
                                                                                                         \
                template <>                                                                              \
                class SerializableRegistration<TYPE>                                                     \
                {                                                                                        \
                    static const ::serializable::detail::RegistryEntry<TYPE>& reg;                       \
                };                                                                                       \
                                                                                                         \
                const ::serializable::detail::RegistryEntry<TYPE>& SerializableRegistration<TYPE>::reg = \
                    ::serializable::detail::RegistryEntry<TYPE>::Instance(::hq::MURMUR3_32(#TYPE));            \
            }                                                                                            \
        }                                                                                                \
    }



// detail impl

namespace serializable
{
    namespace detail
    {
        typedef ::hq::Serializable* (*CreateObjectFunc)();
        typedef std::unordered_map<uint32_t, CreateObjectFunc> SerializableRegistry;

        inline SerializableRegistry& getSerializableRegistry()
        {
            static SerializableRegistry reg;
            return reg;
        }

        template <class T>
        ::hq::Serializable* createSerializable()
        {
            return new T;
        }

        template <class T>
        struct RegistryEntry
        {
        public:
            static RegistryEntry<T>& Instance(const uint32_t typeHash)
            {
                // Because I use a singleton here, even though `REGISTER_SERIALIZABLE_TYPE`
                // is expanded in multiple translation units, the constructor
                // will only be executed once. Only this cheap `Instance` function
                // (which most likely gets inlined) is executed multiple times.

                static RegistryEntry<T> inst(typeHash);
                return inst;
            }

        private:
            RegistryEntry(const uint32_t typeHash)
            {
                SerializableRegistry&  reg  = getSerializableRegistry();
                CreateObjectFunc func = createSerializable<T>;

                std::pair<SerializableRegistry::iterator, bool> ret = reg.insert(SerializableRegistry::value_type(typeHash, func));

                if (ret.second == false)
                {
                    // This means there already is a component registered to
                    // this name. You should handle this error as you see fit.
                }
            }

            RegistryEntry(const RegistryEntry<T>&) = delete;  // C++11 feature
            RegistryEntry& operator=(const RegistryEntry<T>&) = delete;
        };

    }  // detail namespace

}  // serializable namespace
