
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

from bs4 import BeautifulSoup
#driver = webdriver.Chrome("chromedriver")
driver = webdriver.Chrome(ChromeDriverManager().install())

url = "https://www.covid19india.org/state/RJ"
driver.get(url)

soup = BeautifulSoup(driver.page_source, 'html.parser')
results = soup.find(id ='root')
print(results)
