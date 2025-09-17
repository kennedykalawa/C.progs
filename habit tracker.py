import csv
import os
from datetime import datetime
import matplotlib.pyplot as plt
import pandas as pd

DATA_FILE = "habits.csv"

# ------------------------------
# Utility Functions
# ------------------------------
def init_file():
    """Create CSV if not exists"""
    if not os.path.exists(DATA_FILE):
        with open(DATA_FILE, mode="w", newline="") as file:
            writer = csv.writer(file)
            writer.writerow(["date", "habit", "done"])  # headers


def log_habit():
    """Log today's habit completion"""
    date = datetime.now().strftime("%Y-%m-%d")
    habit = input("Enter habit name: ").strip()
    done = input("Done? (y/n): ").strip().lower()

    with open(DATA_FILE, mode="a", newline="") as file:
        writer = csv.writer(file)
        writer.writerow([date, habit, "✅" if done == "y" else "❌"])

    print(f"Habit logged: {habit} → {'✅' if done == 'y' else '❌'}")


def view_today():
    """View today's habits"""
    date = datetime.now().strftime("%Y-%m-%d")
    if not os.path.exists(DATA_FILE):
        print("No data yet.")
        return

    with open(DATA_FILE, mode="r") as file:
        reader = csv.DictReader(file)
        today_habits = [row for row in reader if row["date"] == date]

    if not today_habits:
        print("No habits logged today.")
    else:
        print(f"\n📅 Habits for {date}")
        for row in today_habits:
            print(f"- {row['habit']} {row['done']}")


def visualize_progress():
    """Visualize streaks and completion %"""
    if not os.path.exists(DATA_FILE):
        print("No data to visualize.")
        return

    df = pd.read_csv(DATA_FILE)

    # Count completion per habit
    habit_summary = df.groupby("habit")["done"].apply(lambda x: (x == "✅").sum())

    # Plot bar chart
    habit_summary.plot(kind="bar", color="skyblue")
    plt.title("✅ Habits Completed (All Time)")
    plt.ylabel("Count")
    plt.xlabel("Habit")
    plt.show()

    # Completion percentage over time
    df["done_num"] = df["done"].apply(lambda x: 1 if x == "✅" else 0)
    daily_summary = df.groupby("date")["done_num"].mean() * 100

    daily_summary.plot(kind="line", marker="o", color="green")
    plt.title("📈 Daily Completion %")
    plt.ylabel("Completion (%)")
    plt.xlabel("Date")
    plt.xticks(rotation=45)
    plt.show()


# ------------------------------
# Main CLI Menu
# ------------------------------
def main():
    init_file()
    while True:
        print("\n=== Habit Tracker 🗓️ ===")
        print("1. Log a habit")
        print("2. View today’s habits")
        print("3. Visualize progress")
        print("4. Exit")

        choice = input("Choose an option: ").strip()
        if choice == "1":
            log_habit()
        elif choice == "2":
            view_today()
        elif choice == "3":
            visualize_progress()
        elif choice == "4":
            print("Goodbye! Keep building those streaks 💪")
            break
        else:
            print("Invalid choice. Try again.")


if __name__ == "__main__":
    main()
