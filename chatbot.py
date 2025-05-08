from flask import Flask, request, jsonify
from transformers import pipeline

app = Flask(__name__)

# Optional: Use a HuggingFace model for better responses
qa_pipeline = pipeline("question-answering", model="distilbert-base-cased-distilled-squad")

# Sample knowledge base
knowledge_base = {
    "warranty": "Samsung products typically come with a 1-year standard warranty. You can check your product's warranty on the Samsung website.",
    "repair": "You can schedule a repair from the Support section. Enter your product model and issue description.",
    "order": "To check your order status, log in to your Samsung account and go to 'My Orders'.",
    "mobile": "You can explore Samsung's latest phones under the Mobile section. Check out the Galaxy S and Galaxy A series.",
    "contact": "You can contact Samsung support via chat, phone, or email through the Contact Us page.",
}

# Fallback question answering using transformers
def ai_answer(question):
    context = " ".join(knowledge_base.values())
    response = qa_pipeline({'question': question, 'context': context})
    return response['answer']

@app.route("/chat", methods=["POST"])
def chat():
    user_message = request.json.get("message", "").lower()

    # Keyword-based response
    for key in knowledge_base:
        if key in user_message:
            return jsonify({"response": knowledge_base[key]})

    # Fallback to AI-generated answer
    answer = ai_answer(user_message)
    return jsonify({"response": answer})

@app.route("/")
def index():
    return "Samsung Chatbot API is running!"

if __name__ == "__main__":
    app.run(debug=True)
