package com.eegeo.animation;

import java.util.ArrayList;

import android.animation.Animator;
import android.animation.AnimatorSet;
import android.animation.AnimatorSet.Builder;
import android.animation.ValueAnimator;

public class ReversibleAnimatorSet
{
	private AnimatorSet m_animatorSet = null;
	private Builder m_animatorSetBuilder = null;
	
	public ReversibleAnimatorSet()
	{
		m_animatorSet = new AnimatorSet();
	}
	
	public void addAnimator(ReversibleValueAnimator animator)
	{
		if(m_animatorSetBuilder == null)
		{
			m_animatorSetBuilder = m_animatorSet.play(animator);
		}
		else
		{
			m_animatorSetBuilder.with(animator);
		}
	}
	
	public float getAnimatedFraction()
	{
		float animatedFraction = 1.0f;
		
		ArrayList<Animator> valueAnimators = m_animatorSet.getChildAnimations();
		
		float animatedFractions = 0.0f;
		for(Animator animator : valueAnimators)
		{
			animatedFractions +=((ValueAnimator)animator).getAnimatedFraction();
		}
		
		animatedFraction = animatedFractions/(Math.max(animatedFraction, (float)valueAnimators.size()));

		return animatedFraction;
	}
	
	public void setCurrentPlayTime(long playTimeMilliseconds)
	{
		ArrayList<Animator> valueAnimators = m_animatorSet.getChildAnimations();
		
		for(Animator animator : valueAnimators)
		{
			((ValueAnimator)animator).setCurrentPlayTime(playTimeMilliseconds);
		}
	}
	
	public void start(Animator.AnimatorListener listener, boolean isReversed)
	{
		ArrayList<Animator> valueAnimators = m_animatorSet.getChildAnimations();
		
		for(Animator animator : valueAnimators)
		{
			ReversibleTimeInterpolator reversibleTimeInterpolator = ((ReversibleValueAnimator)animator).getReversibleInterpolator();
			reversibleTimeInterpolator.SetReversed(isReversed);
		}
		
		m_animatorSet.removeAllListeners();
		
		if(listener != null) 
		{
			m_animatorSet.addListener(listener);
		}
		
		m_animatorSet.start();
	}
	
	public long getDurationMilliseconds()
	{
		long durationMilliseconds = 0;
		
		ArrayList<Animator> valueAnimators = m_animatorSet.getChildAnimations();
		
		for(Animator animator : valueAnimators)
		{
			durationMilliseconds = Math.max(durationMilliseconds, ((ValueAnimator)animator).getDuration());
		}
		
		return durationMilliseconds;
	}
	
	public void cancel() 
	{
		if(m_animatorSet.isRunning()) 
		{
			m_animatorSet.cancel();
		}
	}
	
}
