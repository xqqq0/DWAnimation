//
//  UIView+DWAnimation.h
//  DWHUD
//
//  Created by Wicky on 16/8/22.
//  Copyright © 2016年 Wicky. All rights reserved.
//

/*
 UIView (DWAnimation)
 
 简介：基于DWAnimation和DWAnimationManager的UIView扩展
 
 version 1.0.0
 提供UIView扩展动画方法
 
 version 1.0.1
 DWAnimation相关api补充
 
 version 1.0.2
 补充震荡动画api
 */

#import <UIKit/UIKit.h>
#import "DWAnimationManager.h"
@class DWAnimation;
@class DWAnimationMaker;
@interface UIView (DWAnimation)

///以block形式为自身创建动画(移动，缩放，旋转，透明度，圆角，边框宽度，边框颜色，阴影颜色，阴影偏移量，阴影透明度，阴影路径，阴影圆角，背景图)
/*
 animationKey       动画的标识，可为nil
 animationCreater   创建动画的回调Block
 */
-(DWAnimation *)dw_CreateAnimationWithKey:(NSString *)animationKey
                         animationCreater:(void(^)(DWAnimationMaker * maker))animationCreater;

///以数组形式为自身创建动画
/*
 duration           动画时长
 animationKey       动画的标识，可为nil
 animations         动画数组，由CAAnimation及其派生类组成
 */
-(DWAnimation *)dw_CreateAnimationWithBeginTime:(CGFloat)beginTime
                                       duration:(CGFloat)duration
                                  animationKey:(NSString *)animationKey
                                    animations:(__kindof NSArray<CAAnimation *> *)animations;

///以多个状态及时间间隔为自身创建连续动画
/*
 animationType      创建的动画类型
 animationKey       动画的标识
 beginTime          动画延迟时间
 values             动画的状态值数组
 timeIntervals      动画每两个相邻状态间的时间间隔数组
 transition         各个动画状态节点间是否平滑过渡
 
 注：
 animationType的默认属性为DWAnimationTypeMove
 values中第一个数据为动画的初始状态，之后的数据为状
 态节点。timeIntervals是当前状态节点距上一节点的时
 间间隔。如：timeIntervals的第一个数据为第一个状态
 节点距初始状态的时间间隔。故timeIntervals数组元素
 个数应该比values元素个数少1。若参数不正确，则返回nil。
 */
-(DWAnimation *)dw_CreateAnimationWithanimationType:(DWAnimationType)animationType
                                       animationKey:(NSString *)animationKey
                                          beginTime:(CGFloat)beginTime
                                             values:(NSArray *)values
                                      timeIntervals:(NSArray *)timeIntervals
                                         transition:(BOOL)transition;


///以贝塞尔曲线为自身创建移动动画
/*
 animationKey       动画的标识，可为nil
 beginTime          动画延时时长
 duration           动画时长
 bezierPath         运动轨迹，不可为nil
 */
-(DWAnimation *)dw_CreateAnimationWithAnimationKey:(NSString *)animationKey
                           beginTime:(CGFloat)beginTime
                            duration:(CGFloat)duration
                          bezierPath:(UIBezierPath *)bezierPath;

///为自身创建弧线动画
/*
 animationKey       动画的标识，可为nil
 beginTime          动画延时时长
 duration           动画时长
 center             弧线圆心
 radius             弧线半径
 startAngle         弧线的起始角度
 endAngle           弧线的终止角度
 clockwise          是否为顺时针
 autoRotate         是否跟随弧线自动旋转
 */
-(DWAnimation *)dw_CreateAnimationWithAnimationKey:(NSString *)animationKey
                                         beginTime:(CGFloat)beginTime
                                          duration:(CGFloat)duration
                                         arcCenter:(CGPoint)center
                                            radius:(CGFloat)radius
                                        startAngle:(CGFloat)startAngle
                                          endAngle:(CGFloat)endAngle
                                         clockwise:(BOOL)clockwise
                                        autoRotate:(BOOL)autoRotate;

///为自身创建震荡动画
/*
 即改变属性有震荡效果
 
 view               将要展示动画的view，不可为nil
 animationKey       动画的标识，可为nil
 beginTime          动画延时时长
 fromValue          起始值：可为nil或MAXFLOAT或CGPointNull的对象形态，若为nil或MAXFLOAT或CGPointNull的对象形态，则以当前状态作为初始状态
 toValue            终止值：不可为nil
 mass               惯性系数：影响震荡幅度，需大于0。想实现默认效果请传1。
 stiffness          刚性系数：影响震荡速度，需大于0。想实现默认效果请传100。
 damping            阻尼系数：影响震荡停止速度，需大于0。想实现默认效果请传10。
 initialVelocity    初始速度：可正可负，负则先做反向运动，随后正向。想实现默认效果请传0。
 
 注：fromValue与toValue，除DWAnimationSpringTypeMove应为NSValue类型外，其他均应为NSNumber类型数据
 */
-(DWAnimation *)dw_CreateAnimationWithAnimationKey:(NSString *)animationKey
                                     springingType:(DWAnimationSpringType)springingType
                                         beginTime:(CGFloat)beginTime
                                         fromValue:(id)fromValue
                                           toValue:(id)toValue
                                              mass:(CGFloat)mass
                                         stiffness:(CGFloat)stiffness
                                           damping:(CGFloat)damping
                                   initialVelocity:(CGFloat)initialVelocity;

///恢复动画
/*
 beginTime      动画延迟时间
 duration       动画时长
 */
-(DWAnimation *)dw_CreateResetAnimationWithBeginTime:(CGFloat)beginTime
                                            duration:(CGFloat)duration;

///按顺序执行一组动画
/*
 animations     以DWAnimation对象组成的数组
 */
+(void)dw_StartAnimations:(__kindof NSArray<DWAnimation *> *)animations playMode:(DWAnimationPlayMode)playMode;

@end
