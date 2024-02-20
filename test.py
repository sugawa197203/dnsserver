import requests

url = "https://www.tuatmcc.com/"

response = requests.get(url)

print(response.status_code)
print(response.text)

