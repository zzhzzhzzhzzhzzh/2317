# coding: utf8

import gym
import time

def getAction(obs):
    if obs[1]<0:
        return 1
    else:
        return 0


env = gym.make('CartPole-v0')
count = 0
avg = 0
times = 200
for i in range(times):
    env.reset()
    count = 0
    for j in range(1000):
        #action = env.action_space.sample()  #随机采样动作
        if j==0:#小车首次移动
            action = env.action_space.sample()  #随机采样动作
        else:
            action = getAction(observation)
        observation, reward, done, info = env.step(action)  #与环境交互，获得下一步的时刻
        if done:
            break
#env.render()
env.step(env.action_space.sample()) # take a random action
    #print("observation:", observation)
    #print("reward: ",reward)
    #print("")
    count+=1
    #time.sleep(0.2)      #每次等待0.2s
    avg += count
avg = float(avg)/times
env.close()
print("average reward: ",avg)
print(action)
