import requests

with open("rankings.in",mode='w+') as f:
    # The API endpoint URL from which to access the JSON content
    for y in range(1,2000):
        print(f"Page {y}")
        url = f"https://leetcode.com/contest/api/ranking/biweekly-contest-119/?pagination={y}&region=global"

        # Make the GET request
        response = requests.get(url)

        # Check if the request was successful
        if response.status_code == 200:
            # Access the JSON content directly
            json_data = response.json()
            # Extract the 'total_rank' attribute
            total_rank = json_data['total_rank']
            # 'total_rank' now contains the list of user rankings
            #print(total_rank)
            for x in total_rank:
                name = x['username']
                rank = x['rank']
                cn = "com"
                #print(name, x['country_code'])
                if x['data_region'] == 'CN':
                    continue
                url1 = '''https://leetcode.''' + cn + '''/graphql?query=query{userContestRanking(username:"''' + name + '''"){attendedContestsCount rating
                }}'''
                response = requests.get(url1)
                if response.status_code == 200:
                    js = response.json()['data']['userContestRanking']
                    if js is None: #fix later
                        rating = 1500
                        maturity = 0
                    else:
                        rating = js['rating']
                        maturity = js['attendedContestsCount']
                else:
                    print("Fuck")
                print(name,rank,rating,maturity)
                f.write(f"{name} {rank} {rating} {maturity}\n")

        else:
            print(f"Failed to access the data. Status code: {response.status_code}")

        # url1 = '''https://leetcode.com/graphql?query=query{userContestRanking(username:"gtsmarmy"){attendedContestsCount rating
        # }}'''
        # response = requests.get(url1)
        # if response.status_code == 200:
        #     js = response.json()
        #     rating = js['rating']
        #     maturity = js['attendedContestsCount']