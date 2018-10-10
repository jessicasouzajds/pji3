# -*- coding: utf-8 -*-
#Interpreta o arquivo como utf-8 (aceita acentos)

import sys
from flask import Flask, url_for, jsonify, make_response, abort, request, redirect, session
from sqlalchemy import create_engine
from sqlalchemy.sql import text
#from flask_cors import CORS
#from flask_httpauth import HTTPBasicAuth

class ws_gateway():

	def __init__(self):
		eng = create_engine("mysql+pymysql://schaiana:senha123@localhost/pji3")
		try:		
			self.con = eng.connect()
			print('Conectou no banco de dados')
		except:
			print('Não foi possível conectar no banco de dados')
			exit()
		
		self.app = Flask(__name__)
		self.app.env = 'development'
		self.app.add_url_rule('/save_data', view_func=self.save_data, methods=['POST'])
		self.app.run(debug=True)

	def save_data(self): #post	
		request_data = request.get_json()
		response_data = dict()
		response_data['erro'] = 0
		response_data['msg'] = ""

		if not 'gateway_id' in request_data:
			response_data['erro'] = 1
			response_data['msg'] = "É necessário informar o ID do Gateway"
			return jsonify(response_data)
		if not 'sensor_id' in request_data:
			response_data['erro'] = 1
			response_data['msg'] = "É necessário informar o ID do Sensor"
			return jsonify(response_data)
		if not 'dado_sensor' in request_data:
			response_data['erro'] = 1
			response_data['msg'] = "É necessário informar o dado captado pelo sensor"
			return jsonify(response_data)
		if not 'rssi' in request_data:
			response_data['erro'] = 1
			response_data['msg'] = "É necessário informar o ID do Gateway"
			return jsonify(response_data)

		try:
			
			dados = dict()
			dados['gateway_id'] = request_data['gateway_id']
			dados['sensor_id'] = request_data['sensor_id']
			dados['dado'] = request_data['dado_sensor']
			dados['rssi'] = request_data['rssi']


			self._save_bd(dados)
			
		except Exception as inst:
			response_data['erro'] = 1
			response_data['msg'] = "Não foi possível salvar os dados."
			print(inst)
			return jsonify(response_data)

		response_data['msg'] = "Dado inserido no banco."
		return jsonify(response_data)

	def _save_bd(self, dados):
		self.con.execute(text("""INSERT INTO Dado(idGateway, idSensor, dado, RSSI) 
			VALUES(:gateway_id, :sensor_id, :dado, :rssi)"""), **dados)	


if __name__ == '__main__':
	ws = ws_gateway()
