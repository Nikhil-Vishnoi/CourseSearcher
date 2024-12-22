# Package used to curl from the internet 
# To fix requests not found error if on CS225 Coding Environment run 
# following commands
# apt update
# DEBIAN_FRONTEND=noninteractive apt install --yes --no-install-recommends python3-requests 
import requests

# Package used to parse html code 
# To fix requests not found error if on CS225 Coding Environment run 
# following commands
# apt update
# DEBIAN_FRONTEND=noninteractive apt install --yes --no-install-recommends python3-bs4
from bs4 import BeautifulSoup 

import os 

# Package to parse strings 
import re 

# Download the html code of the url to a .html file in the download location 
def downloadhtml(url, loc, filename):
    # Query the website source code using requests python library 
    website = requests.get(url).text
    # Write website to html file labeled loc/filename.txt 
    file = open((loc+'/'+filename),'w') 
    file.write(website)
    file.close()
# Open a file into a string for mode 
def openfile(loc, filename, mode): 
    if(mode == 'r'):
        f = open((loc+'/'+filename),mode) 
        stored = f.read()
        f.close()
        return stored 
    return open((loc+'/'+filename),mode)
if __name__ == "__main__":
    data_folder = "data_dump"
    # Create a data_dump folder. This folder should be inside the .gitignore 
    try:
        os.mkdir(data_folder)
    except FileExistsError:
        # Do nothing 
        1+1

    catalog = 'http://catalog.illinois.edu'
    parent = '/courses-of-instruction/'
    # Download the parent data 
    downloadhtml((catalog+parent),data_folder,"academic_catalog.html")
    bs = BeautifulSoup(openfile(data_folder,'academic_catalog.html','r'), 'html.parser')
    links = []
    for link in bs.findAll('a'):
        try:
            if(link.get('href').find(parent) != -1): 
                if(len(link.get('href')) > len(parent)) and link.get('href').find('.pdf')==-1: 
                    links.append(link.get('href'))
        except AttributeError: 
            1+1

    # Go through the courses of instruction page and get the mini links of every html page  
    files = []
    for link in links:
        filename = link.replace(parent,'').replace('/','')+'.html'
        downloadhtml((catalog+link),data_folder,filename)
        files.append(filename) 
        #print(link)
        print(filename)
        # break 
    product = openfile(data_folder,'courses.csv','w') 
    product.write("Course Code, Course Name, Credit Hours, Course Description, Prereq, Coreq\n")
    # Go through all the files and generate our csv 
    for fileloc in files:
        bs = BeautifulSoup(openfile(data_folder,fileloc,'r'), 'html.parser')
        courses = bs.find_all('p',class_='courseblocktitle')
        courseinfo = bs.find_all('p',class_='courseblockdesc')
        #print(len(courses))
        #print(len(courseinfo))
        i = 0
        while i < len(courses):
           # print(courses[i].get_text()) 
            # Courses are started with a tab delimiter 
            courseheader = courses[i].get_text()
            courseheader_augmented = courseheader.replace(' ','|')
            print(courseheader)
            print(courseheader_augmented)
            courseCode = courseheader[0:courseheader_augmented.find('|')]
            courseName = courseheader[courseheader_augmented.find('|'):courseheader.find('credit')].strip()
            creditHours = [] 
            courseInfo = courseinfo[i].get_text().strip().replace('\xa0',' ')
            for char in courseheader[courseheader_augmented.find('|'):]:
                if char.isnumeric(): 
                    creditHours.append(char)


            #print(courseCode)
            #print(courseName)
            #print(creditHours)
            #print(courseinfo[i].get_text())
            product.write(courseCode)
            product.write('|')
            product.write(courseName)
            product.write('|[')
            c = 0
            for ch in creditHours:
                if(c != 0):
                    product.write('_')
                product.write(ch) 
                c = c + 1
            product.write(']|')
            product.write(courseInfo)
            product.write('|[') 

            y = re.findall(r"[A-Z]{2,5} [0-9]{3}", courseInfo)
            lol = 0 
            for course in y: 
                product.write(course)
                if(lol+1<len(y)): 
                    product.write('_')
                lol = lol + 1



                #break 
            product.write(']\n')
            i = i + 1
            # Uncomment this break once you have figured out how to parse the stuff 
            #break 
            #print(info)
    product.close()

   #s print(openfile(data_folder,"academic_catalog.html"))



    
    