# coding: utf8

import numpy as np
import gym
import time

def get_action(weights, observation):#根据权值与当前状态算出决策值
    act = np.dot(weights[:4], observation) + weights[4]   #计算加权和
    if act >= 0:
        return 1
    else:
        return 0

def get_avg_reward_by_weights(env, weights):
    # 测试不同权值下模型的平均持续时间
    sum_reward = 0 # 记录奖励
    times = 20
    for i in range(times):
        observation = env.reset() # 重置初始状态
        count = 0
        c_reward = 0
        for t in range(1000):
            # time.sleep(0.01)
            # env.render()
            action = get_action(weights, observation) # 获取当前权值下的决策动作
            observation, reward, done, info = env.step(action)# 执行动作并获取这一动作下的下一时间步长状态
            c_reward += reward
            if done or c_reward >= 200:# 如若游戏结束，返回
                break
        sum_reward += c_reward
    return float(sum_reward)/times

def get_weights_by_hill_climbing(best_weights):
    # 通过爬山算法选取权值（在当前最好权值上加入随机值）
    return best_weights + np.random.normal(0, 0.1, 5)

def get_best_result():
    env = gym.make("CartPole-v0")
    np.random.seed(10)
    best_reward = 0 # 奖励初始化
    best_weights = np.random.rand(5) # 初始权值为随机取值
    for iter in range(10000):# 迭代10000次
        cur_weights = None
        cur_weights = get_weights_by_hill_climbing(best_weights)#获得调整后的权值
        # 获取当前权值的奖励
        cur_sum_reward = get_avg_reward_by_weights(env, cur_weights)
        # 更新当前最优权值
        if cur_sum_reward > best_reward:
            best_reward = cur_sum_reward
            best_weights = cur_weights
        # 达到最佳奖励阈值后结束
        if best_reward >= 200:
            break
    print("average reward: ",get_avg_reward_by_weights(env, best_weights))
    return best_reward, best_weights

# 程序从这里开始执行
print("weights: ", get_best_result()[1]) # 调用爬山算法寻优并输出结果


