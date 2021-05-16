import requests
from bs4 import BeautifulSoup
import pandas as pd

URL = 'https://www.grainmart.in/news/covid-19-coronavirus-india-state-and-district-wise-tally/'
page = requests.get(URL)

soup = BeautifulSoup(page.content, 'html.parser')
results = soup.find(id='covid-19-table')
st = input("Enter the state: ")
st =st.title()
states = results.find_all("div", class_ = 'skgm-states')
for state in states:
  if(str(state).find(st) != -1):
  	state_need = state
extract = state_need.find_all("div", class_ = 'skgm-td')
districts = []
cases = []
for i in range(10,len(extract), 5):
	districts.append(str(extract[i])[21:-6])
for i in range(11, len(extract), 5):
	case = str(extract[i].find('div', class_ = 'td-dc'))
	cases.append(case[19:-6]) 
data = {'Districts': districts, 'Confirmed Cases': cases}
output = pd.DataFrame(data)
output.to_csv('Cases in '+st +'.csv')