#!/usr/bin/env python
# coding: utf-8

# In[1]:


import streamlit as st


# In[2]:


"""
    Dataset: http://www.gutenberg.org/cache/epub/5200/pg5200.txt
    Remove all the unnecessary data and label it as Metamorphosis-clean.
    The starting and ending lines should be as follows.

"""


file = open("C:/Users/BHARATHWAJ T A/Desktop/AIDI Durham/20F/AIDI1002/metamorphosis_clean.txt", "r",encoding = "utf8")
lines = []

for i in file:
    lines.append(i)


# In[3]:


for i in lines:
    data = ' '. join(lines)
    
data = data.replace('\n', '').replace('\r', '').replace('\ufeff', '')
length=data


# In[4]:


dataLength=len(length)
dataLength


# In[5]:


word=st.text_input("Word","")
wordLength=len(word)
st.write(wordLength)


# In[6]:


letter=0
letterInText=0
startingLetter=0
endingLetter=0
m=1
n=1

startLetters=[]
endLetters=[]
wordPredict=[]

for initialize in range(dataLength):
    startLetters.append(0)
    endLetters.append(0)
    wordPredict.append(0)


# In[ ]:


initialize=0

for index in range(dataLength):
    while m in range(wordLength):
        if word[letter:letter+m] in length[letterInText:letterInText+n]:
            if m==1:
                print("\n")
                startLetters[initialize]=letterInText
                startingLetter=startLetters[initialize]
            m+=1
            n+=1
        else:
            m=1
            n=1
            letterInText+=1
            
            if (letterInText==dataLength):
                index=letterInText
                break
    
    if (letterInText<dataLength):
        endLetters[initialize]=letterInText+n
        letterInText=endLetters[initialize]
        searchedWord=length[startLetters[initialize]:endLetters[initialize]]
        
    
    predict=letterInText+1
    while predict in range(dataLength):
        if (" " in length[predict])or("," in length[predict])or("." in length[predict])or(";" in length[predict]):
            predictedWord=length[startLetters[initialize]:(predict)]
            predict=0
            break
        else:
            predict+=1
    
    wordPredict[initialize]=predictedWord
    initialize+=1
    m=1
    n=1
    if (index==dataLength):
        break


# In[ ]:


print("Typed Word: ",searchedWord)

for index in range(dataLength):
    if(wordPredict[index]!=0):
        print("Word Predict: ",wordPredict[index])
        st.write("Word Predict: ",wordPredict[index])

