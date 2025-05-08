class LibraryExpertSystem:

    def __init__(self):
        # Knowledge base (subject → recommended books)
        self.knowledge_base = {
            'artificial intelligence': ['Artificial Intelligence: A Modern Approach by Russell & Norvig', 
                                        'Python AI Projects by Joshua Eckroth'],
            'machine learning': ['Hands-On Machine Learning by Aurélien Géron', 
                                 'Machine Learning Yearning by Andrew Ng'],
            'web development': ['Eloquent JavaScript by Marijn Haverbeke', 
                                'Learning Web Design by Jennifer Niederst Robbins'],
            'data science': ['Python for Data Analysis by Wes McKinney', 
                             'Data Science from Scratch by Joel Grus'],
            'cybersecurity': ['Cybersecurity for Beginners by Raef Meeuwisse', 
                              'The Web Application Hacker\'s Handbook by Dafydd Stuttard']
        }

    def recommend_books(self, project_topic):
        topic = project_topic.lower()
        for subject in self.knowledge_base:
            if subject in topic:
                return f"Recommended books for '{project_topic}':\n" + '\n'.join(self.knowledge_base[subject])
        return "Sorry, no recommendations found for this project topic."

# Example usage:
expert = LibraryExpertSystem()

# Simulate input
user_topic = input("Enter your project topic: ")
print(expert.recommend_books(user_topic))
