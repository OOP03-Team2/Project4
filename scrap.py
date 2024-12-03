from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import Select  # To handle dropdown menu
import csv
import time


# Function to save data to CSV
def save_to_csv(filename, data, league):
    """
    Save extracted data to a CSV file.

    :param filename: The name of the CSV file.
    :param mode: Write over or append
    :param data: A list of lists containing the row data.
    :param headers: Optional header for the CSV file.
    """
    # Open the CSV file for writing
    if league == "Premier League" or league == "premier-league":
        mode = 'w'
    else:
        mode = 'a'
    with open(filename, mode, newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        
        writer.writerow([league])
        for row in data:
            # Remove '%' from each value in the row if it contains a percentage
            row = [value.replace('%', '') if isinstance(value, str) and '%' in value else value for value in row]
            writer.writerow(row)
        writer.writerow([])

# Function to extract football prediction data for a specific league
def extract_prediction_data(driver, league):
    """
    Extract football predictions for a specific league.

    :param driver: Selenium WebDriver instance.
    :param league: The name of the league.
    :return: Extracted data as a list of lists, along with the header.
    """

    league_dropdown = driver.find_element(By.CSS_SELECTOR, "select._category-selector_1n038_18")
    #select = Select(league_dropdown)
    Select(league_dropdown).select_by_visible_text(league)

    # Wait for the table to update after selecting the league
    WebDriverWait(driver, 10).until(
        EC.visibility_of_element_located((By.CSS_SELECTOR, "table._data-table_1mnv2_1"))  # Wait for the table to reload
    )
    time.sleep(1.5)

    # Locate the table rows
    rows = driver.find_elements(By.CSS_SELECTOR, "div._data-table-container_1mnv2_1 table._data-table_1mnv2_1 tr")


    data = []
    # Loop through each row and determine how many predicted positions (columns) we have
    for row in rows[1:]:  # Skip the first row if it's the header row
        columns = row.find_elements(By.TAG_NAME, "td")
        num_positions = len(columns) - 2

        # Extract data
        position = columns[0].text
        team = columns[1].text
        predicted_positions = [column.text.strip() for column in columns[2:2 + num_positions]]
        
        # Check that the predicted positions list has the correct length
        if len(predicted_positions) == num_positions:
            data.append([position, team] + predicted_positions)

    return data

# Function to extract current data in football
def extract_table_data(driver, league):
    driver.get(f"https://theanalyst.com/eu/competition/{league}/table")
    
    # Wait for the table to update after selecting the league
    WebDriverWait(driver, 10).until(
        EC.visibility_of_element_located((By.CSS_SELECTOR, "table.Table-module_data-table__J-DUE"))  # Wait for the table to reload
    )
    time.sleep(1.5)

    # Locate the table rows
    rows = driver.find_elements(By.CSS_SELECTOR, "table.Table-module_data-table__J-DUE tr")
    
    
    data = []
    # Loop through each row and determine how many predicted positions (columns) we have
    for row in rows[1:]:
        columns = row.find_elements(By.TAG_NAME, "td")

        # Extract data about current table
        temp = [column.text.strip() for column in columns[0:-2]]
        temp.append(columns[-1].text.strip())
        
        if len(temp) == len(columns) - 1:
            data.append(temp)

    # Scroll down the page a little bit to ensure the button is in view
    driver.execute_script("window.scrollTo(0, 500)")  # Scrolls 500px down
    time.sleep(1)
    # Locate the "Predicted" button using CSS (or XPath, depending on your choice)
    predicted_button = driver.find_element(By.XPATH, "//button[contains(text(), 'PREDICTED')]")
    WebDriverWait(driver, 10).until(EC.element_to_be_clickable(predicted_button))
    predicted_button.click()
    predicted_table = WebDriverWait(driver, 10).until(
        EC.visibility_of_element_located((By.CSS_SELECTOR, "table.Table-module_data-table__J-DUE"))
    )
    time.sleep(1)
    rows = predicted_table.find_elements(By.TAG_NAME, "tr")

    x_pts = []
    for row in rows[1:]:
        columns = row.find_elements(By.TAG_NAME, "td")

        # Extract data about XPTS
        x_pts.append(columns[2].text.strip())

    for i, item in enumerate(data):
        item.append(x_pts[i])  # Append the corresponding new_info to each inner list


    return data

chrome_options = Options()
chrome_options.add_argument("--headless")
chrome_options.add_argument("--no-sandbox")
chrome_options.add_argument("--disable-dev-shm-usage")


# Initialize WebDriver
driver = webdriver.Chrome(options=chrome_options)
driver.get("https://dataviz.theanalyst.com/opta-football-predictions/")
# Wait for the table to load
WebDriverWait(driver, 50).until(
    EC.visibility_of_element_located((By.CSS_SELECTOR, "table._data-table_1mnv2_1"))
)

leagues = [
    ["Premier League", "premier-league"],
    ["Serie A", "serie-a"],
    ["La Liga", "la-liga"],
    ["Bundesliga", "bundesliga"],
    ["Ligue 1", "ligue-1"]
]
for league in leagues:
    data = extract_prediction_data(driver, league[0])
    save_to_csv("prediced_table.csv", data, league[0])    
time.sleep(1)
for league in leagues:
    data = extract_table_data(driver, league[1])
    save_to_csv("current_table.csv", data, league[1])

driver.quit()
print("Data extraction and CSV writing completed!")

