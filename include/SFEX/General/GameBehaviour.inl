#include "GameBehaviour.hpp"

namespace sfex
{

template<typename T>
void BehaviourDeleter<T>::operator()(T* ptr) const
{
    // ptr->onDestroy();
    delete ptr;
}

}