from datetime import datetime, timedelta

class AirlineExpertSystem:
    def __init__(self):
        self.knowledge_base = {
            'aircrafts': [
                {'id': 'A330-1', 'type': 'A330', 'pax_cap': 300, 'cargo_cap': 20, 'range': 11750, 'speed': 871, 'turnaround': 90, 'location': 'JFK', 'status': 'available'},
                {'id': 'B777-1', 'type': 'B777', 'pax_cap': 400, 'cargo_cap': 30, 'range': 13650, 'speed': 892, 'turnaround': 120, 'location': 'LAX', 'status': 'available'}
            ],
            'routes': [
                {'route_id': 'RT1', 'origin': 'JFK', 'dest': 'LHR', 'distance': 5500, 'pax_demand': 250, 'cargo_demand': 18, 'base_fare': 800, 'cargo_rate': 4.5, 'departure_times': ['08:00', '20:00']},
                {'route_id': 'RT2', 'origin': 'LAX', 'dest': 'HND', 'distance': 5500, 'pax_demand': 300, 'cargo_demand': 25, 'base_fare': 1000, 'cargo_rate': 5.0, 'departure_times': ['09:00', '21:00']}
            ],
            'cargo_requests': [
                {'id': 'C1', 'origin': 'JFK', 'dest': 'LHR', 'weight': 15, 'volume': 12, 'priority': 1, 'revenue': 12000, 'deadline': '2023-12-15'},
                {'id': 'C2', 'origin': 'LAX', 'dest': 'HND', 'weight': 20, 'volume': 15, 'priority': 2, 'revenue': 22000, 'deadline': '2023-12-16'}
            ],
            'schedule': [],
            'flight_counter': 1,
            'current_date': datetime(2023, 12, 10)
        }

    def recommend_flight(self, route_id, departure_time=None):
        route = next((r for r in self.knowledge_base['routes'] if r['route_id'] == route_id), None)
        if not route:
            return f"Route {route_id} not found"

        if not departure_time:
            departure_time = route['departure_times'][0]

        aircrafts = [a for a in self.knowledge_base['aircrafts']
                     if a['location'] == route['origin']
                     and a['range'] >= route['distance']
                     and a['status'] == 'available']
        if not aircrafts:
            return "No available aircraft for this route"

        flight_hours = route['distance'] / aircrafts[0]['speed']
        flight_duration = timedelta(hours=flight_hours)
        best_aircraft = aircrafts[0]

        flight_id = f"FLT-{self.knowledge_base['flight_counter']:03d}"
        dep_dt = datetime.strptime(f"{self.knowledge_base['current_date'].date()} {departure_time}", "%Y-%m-%d %H:%M")
        arr_dt = dep_dt + flight_duration

        revenue = route['base_fare'] * route['pax_demand'] + route['cargo_rate'] * route['cargo_demand'] * 1000
        flight_details = {
            'id': flight_id, 'route': route_id, 'origin': route['origin'], 'dest': route['dest'],
            'aircraft': best_aircraft['id'], 'departure_time': dep_dt, 'arrival_time': arr_dt,
            'status': 'scheduled', 'projected_revenue': revenue
        }

        best_aircraft['status'] = 'scheduled'
        best_aircraft['location'] = route['dest']
        self.knowledge_base['schedule'].append(flight_details)
        self.knowledge_base['flight_counter'] += 1

        return f"Flight {flight_id} scheduled on {departure_time} using {best_aircraft['id']}.\nRevenue: ${revenue}"

    def optimize_cargo(self, flight_id):
        flight = next((f for f in self.knowledge_base['schedule'] if f['id'] == flight_id), None)
        if not flight:
            return f"Flight {flight_id} not found"

        route = next(r for r in self.knowledge_base['routes'] if r['route_id'] == flight['route'])
        aircraft = next(a for a in self.knowledge_base['aircrafts'] if a['id'] == flight['aircraft'])

        cargo_options = [c for c in self.knowledge_base['cargo_requests']
                         if c['origin'] == route['origin'] and c['dest'] == route['dest']
                         and datetime.strptime(c['deadline'], '%Y-%m-%d').date() >= flight['arrival_time'].date()]
        cargo_options.sort(key=lambda x: x['priority'] * x['revenue'], reverse=True)

        total_weight = total_volume = total_revenue = 0
        loaded = []
        for c in cargo_options:
            if total_weight + c['weight'] <= aircraft['cargo_cap'] and total_volume + c['volume'] <= aircraft['cargo_cap']:
                total_weight += c['weight']
                total_volume += c['volume']
                total_revenue += c['revenue']
                c['status'] = f"loaded on {flight_id}"
                loaded.append(c['id'])

        return f"Cargo loaded: {loaded}\nRevenue: ${total_revenue}"

    def list_routes(self):
        return "\n".join([f"{r['route_id']}: {r['origin']}->{r['dest']} ({r['pax_demand']} pax)" for r in self.knowledge_base['routes']])

    def list_aircraft(self):
        return "\n".join([f"{a['id']} ({a['type']} at {a['location']}) - {a['status']}" for a in self.knowledge_base['aircrafts']])

    def list_schedule(self):
        return "\n".join([f"{f['id']} {f['origin']}->{f['dest']} ({f['departure_time'].strftime('%H:%M')})" for f in self.knowledge_base['schedule']]) or "No flights scheduled"

    def chat_interface(self):
        print("Welcome to the Airline Expert System")
        while True:
            query = input("\nYour query: ").strip().lower()
            if query in ['exit', 'quit']:
                print("Goodbye!")
                break
            elif 'recommend flight' in query:
                print(self.list_routes())
                route_id = input("Enter route ID: ").upper()
                time = input("Enter departure time (blank for earliest): ")
                print(self.recommend_flight(route_id, time or None))
            elif 'optimize cargo' in query:
                print(self.list_schedule())
                fid = input("Enter flight ID: ").upper()
                print(self.optimize_cargo(fid))
            elif 'list routes' in query:
                print(self.list_routes())
            elif 'list aircraft' in query:
                print(self.list_aircraft())
            elif 'list schedule' in query:
                print(self.list_schedule())
            else:
                print("Unknown command. Try: recommend flight, optimize cargo, list routes, list aircraft, list schedule, exit")

if __name__ == "__main__":
    expert = AirlineExpertSystem()
    expert.chat_interface()



Questions :
🛫 Flight Scheduling
"Recommend a flight for route RT1."

"I want to schedule a flight from JFK to LHR. What aircraft are available?"

"Schedule a flight for route RT2 at 09:00."

"Which aircraft can serve route RT2 based on range and availability?"

📦 Cargo Optimization
"Optimize cargo for the flight FLT-001."

"What cargo can be loaded for a JFK to LHR flight based on capacity and deadline?"

"How much revenue can I generate from loading cargo on FLT-002?"

📋 Data Exploration
"List all available routes."

"What aircraft are currently available and where are they located?"

"Show the scheduled flights."

"How many passengers can be carried on route RT1?"

"What is the projected revenue of flight FLT-001?"

⚙️ Testing System Behavior
"What happens if no aircraft is available at the origin airport?"

"Can I schedule multiple flights for the same route in one day?"

"Will the system reject cargo that exceeds aircraft capacity?"