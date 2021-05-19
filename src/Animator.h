#pragma once
#include <memory>
#include <map>
#include <type_traits>
#include "Animation.h"


// After I have learned template, 
// I used it to ask for an Enum for any object: player'state, enemy's state..


template<typename AnimationState, class Enable = void>
class Animator;
template<typename AnimationState>
class Animator<AnimationState, typename std::enable_if<std::is_enum<AnimationState>::value>::type>
{
protected:
    //std::shared_ptr<C_Sprite> sprite; 
    std::map<AnimationState, std::shared_ptr<Animation>> m_Animations;

    // store a reference to the current animation so we can quickly update and draw it.
    std::pair<
        AnimationState,
        std::shared_ptr<Animation>> m_oCurrentAnimation;

public:
    /*   Animator();
       const SimpleImage& play();
       void addAnimation(AnimationState state,
           std::shared_ptr<Animation> animation);
       void setAnimationState(AnimationState state);
       const AnimationState& getAnimationState() const;
   */

    Animator() {};
    ~Animator() {};

    void Animator::addAnimation(
        AnimationState state, std::shared_ptr<Animation> animation)
    {
        auto inserted = m_Animations.insert(std::make_pair(state, animation));
        //std::cout << AnimationState::None << std::endl;
        //std::cout << PlayerState::None << std::endl;
        //if (m_oCurrentAnimation.first == AnimationState::None) {
        //    setAnimationState(state);
        //}
    }

    void Animator::setAnimationState(AnimationState state)
    {
        if (m_oCurrentAnimation.first == state)
            return;

        auto animation = m_Animations.find(state);
        if (animation != m_Animations.end())
        {
            m_oCurrentAnimation.first = animation->first;
            m_oCurrentAnimation.second = animation->second;
            // reset this animation to be played!
            m_oCurrentAnimation.second->reset();
        }
    }

    const AnimationState& Animator::getAnimationState() const {
        return m_oCurrentAnimation.first;
    }

    const SimpleImage& Animator::play()
    {
        m_oCurrentAnimation.second->updateFrame();
        return m_oCurrentAnimation.second->getCurrentFrame();
    }
};
