#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->frame.clear();
	vector<ofColor> color_list = { ofColor(255, 0, 0), ofColor(0, 255, 0), ofColor(0, 0, 255) };

	for (int len = 100; len <= 250; len += 150) {
		
		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		for (int i = 0; i < color_list.size(); i++) {

			auto angle_x = ofMap(ofNoise(noise_seed.x, i * 0.008 + ofGetFrameNum() * 0.0035), 0, 1, -PI, PI);
			auto angle_y = ofMap(ofNoise(noise_seed.y, i * 0.008 + ofGetFrameNum() * 0.0035), 0, 1, -PI, PI);
			auto angle_z = ofMap(ofNoise(noise_seed.z, i * 0.008 + ofGetFrameNum() * 0.0035), 0, 1, -PI, PI);

			auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

			auto index = this->frame.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(len * -0.5, len * 0.5, len * -0.5));
			vertices.push_back(glm::vec3(len * 0.5, len * 0.5, len * -0.5));
			vertices.push_back(glm::vec3(len * 0.5, len * 0.5, len * 0.5));
			vertices.push_back(glm::vec3(len * -0.5, len * 0.5, len * 0.5));

			vertices.push_back(glm::vec3(len * -0.5, len * -0.5, len * -0.5));
			vertices.push_back(glm::vec3(len * 0.5, len * -0.5, len * -0.5));
			vertices.push_back(glm::vec3(len * 0.5, len * -0.5, len * 0.5));
			vertices.push_back(glm::vec3(len * -0.5, len * -0.5, len * 0.5));

			for (auto& vertex : vertices) {

				vertex = glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_x;
				this->frame.addColor(color_list[i]);
			}

			this->frame.addVertices(vertices);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
			this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
			this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);
			this->frame.addIndex(index + 3); this->frame.addIndex(index + 0);

			this->frame.addIndex(index + 4); this->frame.addIndex(index + 5);
			this->frame.addIndex(index + 5); this->frame.addIndex(index + 6);
			this->frame.addIndex(index + 6); this->frame.addIndex(index + 7);
			this->frame.addIndex(index + 7); this->frame.addIndex(index + 4);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 4);
			this->frame.addIndex(index + 1); this->frame.addIndex(index + 5);
			this->frame.addIndex(index + 2); this->frame.addIndex(index + 6);
			this->frame.addIndex(index + 3); this->frame.addIndex(index + 7);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}