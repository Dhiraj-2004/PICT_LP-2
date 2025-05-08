class SocietyExpertSystem:
    def __init__(self):
        # Initial facts
        self.facts = {
            'day': 'Monday',
            'pump_maintenance': True,
            'light_fault_reported': True,
            'power_cut': False
        }
        self.conclusions = {}

    def infer(self):
        # Rule 1: No water on Monday due to pump maintenance
        if self.facts['day'] == 'Monday' and self.facts['pump_maintenance']:
            self.conclusions['water_supply'] = False
            self.conclusions['water_reason'] = "Pump maintenance on Monday"

        # Rule 2: No lights due to fault or power cut
        if self.facts['light_fault_reported'] or self.facts['power_cut']:
            self.conclusions['common_lights'] = False
            if self.facts['light_fault_reported']:
                self.conclusions['light_reason'] = "Light fault reported"
            else:
                self.conclusions['light_reason'] = "Power cut"

    def answer_question(self, question):
        self.infer()

        if "water" in question.lower():
            if self.conclusions.get('water_supply') is False:
                return f"No water supply on {self.facts['day']}: {self.conclusions['water_reason']}"
            else:
                return "Water supply was normal."

        elif "light" in question.lower() or "lights" in question.lower():
            if self.conclusions.get('common_lights') is False:
                return f"No lights in common passage: {self.conclusions['light_reason']}"
            else:
                return "Common lights were working normally."

        else:
            return "Sorry, I don't understand the question."


# Demo
expert = SocietyExpertSystem()

print(expert.answer_question("Why was there no water supply on Monday?"))
print(expert.answer_question("Why were there no lights in common passage?"))
