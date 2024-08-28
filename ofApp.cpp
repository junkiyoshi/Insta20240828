#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	int size = 30;
	int z = 300;

	for (int i = 0; i < 4; i++) {

		for (int len = 300; len > 100; len -= 25) {

			z = ofMap(len, 0, 300, 0, 300);
			size = ofMap(len, 0, 300, len / 5, len / 10);
			for (int x = -len + size * 0.5; x <= len - size * 0.5; x += size) {

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec3(x - size * 0.5, 0, z));
				vertices.push_back(glm::vec3(x - size * 0.5, 0, z));
				vertices.push_back(glm::vec3(x + size * 0.5, 0, z));
				vertices.push_back(glm::vec3(x + size * 0.5, 0, z));

				glm::highp_mat4 rotation;
				rotation = glm::rotate(glm::mat4(), ofMap(i, 0, 4, 0, 360) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));

				for (auto& vertex : vertices) {

					vertex = glm::vec4(vertex, 0) * rotation;
				}

				int height = ofMap(ofNoise(glm::vec4(vertices[0] * 0.01, ofGetFrameNum() * 0.05)), 0, 1, 0, 100 + 1000);
				vertices[1].y = height;
				vertices[2].y = height;

				this->face.addVertices(vertices);
				this->line.addVertices(vertices);

				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 3);
				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);

				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 3);
				this->line.addIndex(this->line.getNumVertices() - 3); this->line.addIndex(this->line.getNumVertices() - 4);
				this->line.addIndex(this->line.getNumVertices() - 4); this->line.addIndex(this->line.getNumVertices() - 1);

				for (int i = 0; i < vertices.size(); i++) {

					this->face.addColor(ofColor(64, 164, 255, 64));
					this->line.addColor(ofColor(64, 164, 255));
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);

	this->face.draw();
	this->line.drawWireframe();

	this->cam.end();

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}