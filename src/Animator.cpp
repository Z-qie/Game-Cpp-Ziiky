//#pragma once
//#include <memory>
//#include <map>
//#include "Animation.h"
//#include "Animator.h"
//
//Animator::Animator() {};
//
//void Animator::addAnimation(
//    AnimationState state, std::shared_ptr<Animation> animation)
//{
//    auto inserted = m_Animations.insert(std::make_pair(state, animation));
//
//    if (m_oCurrentAnimation.first == AnimationState::None)
//        setAnimationState(state);
//}
//
//void Animator::setAnimationState(AnimationState state)
//{
//    if (m_oCurrentAnimation.first == state)
//        return;
//
//    auto animation = m_Animations.find(state);
//    if (animation != m_Animations.end())
//    {
//        m_oCurrentAnimation.first = animation->first;
//        m_oCurrentAnimation.second = animation->second;
//
//        // reset this animation to be played!
//        m_oCurrentAnimation.second->reset();
//    }
//}
//
//const AnimationState& Animator::getAnimationState() const {
//    return m_oCurrentAnimation.first;
//}
//
//const SimpleImage& Animator::play()
//{
//    if (m_oCurrentAnimation.first != AnimationState::None)
//        if (m_oCurrentAnimation.second->updateFrame())
//            return m_oCurrentAnimation.second->getCurrentFrame();
//}