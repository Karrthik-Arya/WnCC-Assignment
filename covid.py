import requests
from bs4 import BeautifulSoup
import pandas as pd

URL = 'https://www.grainmart.in/news/covid-19-coronavirus-india-state-and-district-wise-tally/'
page = requests.get(URL) #extract the webpage 

soup = BeautifulSoup(page.content, 'html.parser') #create a soup object
results = soup.find(id='covid-19-table') #div containg the data that we need
st = input("Enter the state: ")
st =st.title()
states = results.find_all("div", class_ = 'skgm-states') #creates an iterable object each containg the data for a state
for state in states:
  if(str(state).find(st) != -1):
  	state_need = state
extract = state_need.find_all("div", class_ = 'skgm-td') #get data for the state entered by the user
districts = []
cases = []
for i in range(10,len(extract), 5):
	districts.append(str(extract[i])[21:-6]) # extract district names
for i in range(11, len(extract), 5):
	case = str(extract[i].find('div', class_ = 'td-dc'))
	cases.append(case[19:-6]) #extract no. of confirmed covid cases in each district
data = {'Districts': districts, 'Confirmed Cases': cases}
output = pd.DataFrame(data) #create dataframe from the scraped data
output.to_csv('Cases in '+st +'.csv') #export it as csv