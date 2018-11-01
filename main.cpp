//#include "opencv2/video/tracking.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//#include <stdio.h>
//using namespace std;
//using namespace cv;
//
////������Դ��ڵ�����ֵ����Ϊ����ԭ�������Ͻǣ�����sinǰ�и�����
//static inline Point calcPoint(Point2f center, double R, double angle)
//{
//	return center + Point2f((float)cos(angle), (float)-sin(angle))*(float)R;
//}
//
//static void help()
//{
//	printf("\nExamle of c calls to OpenCV's Kalman filter.\n"
//		"   Tracking of rotating point.\n"
//		"   Rotation speed is constant.\n"
//		"   Both state and measurements vectors are 1D (a point angle),\n"
//		"   Measurement is the real point angle + gaussian noise.\n"
//		"   The real and the estimated points are connected with yellow line segment,\n"
//		"   the real and the measured points are connected with red line segment.\n"
//		"   (if Kalman filter works correctly,\n"
//		"    the yellow segment should be shorter than the red one).\n"
//		"\n"
//		"   Pressing any key (except ESC) will reset the tracking with a different speed.\n"
//		"   Pressing ESC will stop the program.\n"
//	);
//}
//
//int main(int, char**)
//{
//	help();
//	Mat img(500, 500, CV_8UC3);
//	KalmanFilter KF(2, 1, 0);                                    //�����������˲�������KF
//	Mat state(2, 1, CV_32F);                                     //state(�Ƕȣ����Ƕ�)
//	
//	Mat processNoise(2, 1, CV_32F);
//	Mat measurement = Mat::zeros(1, 1, CV_32F);                 //�������ֵ
//	char code = (char)-1;
//
//	for (;;)
//	{
//		//1.��ʼ��
//		randn(state, Scalar::all(0), Scalar::all(0.1));
//		KF.transitionMatrix = (Mat_<float>(2, 2) << 1, 1, 0, 1);  //ת�ƾ���A[1,1;0,1]    
//
//
//																   //�����漸����������Ϊ�Խ���
//		setIdentity(KF.measurementMatrix);                             //��������H
//		setIdentity(KF.processNoiseCov, Scalar::all(1e-5));            //ϵͳ�����������Q
//		setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));        //���������������R
//		setIdentity(KF.errorCovPost, Scalar::all(1));                  //����������Э�������P
//
//		randn(KF.statePost, Scalar::all(0), Scalar::all(0.1));          //x(0)��ʼ��
//
//		for (;;)
//		{
//			Point2f center(img.cols*0.5f, img.rows*0.5f);          //centerͼ�����ĵ�
//			float R = img.cols / 3.f;                                //�뾶
//			double stateAngle = state.at<float>(0);                //���ٵ�Ƕ�
//			Point statePt = calcPoint(center, R, stateAngle);     //���ٵ�����statePt
//
//																  //2. Ԥ��
//			Mat prediction = KF.predict();                       //����Ԥ��ֵ������x'
//			double predictAngle = prediction.at<float>(0);          //Ԥ���ĽǶ�
//			Point predictPt = calcPoint(center, R, predictAngle);   //Ԥ�������predictPt
//
//
//																	//3.����
//																	//measurement�ǲ���ֵ
//			randn(measurement, Scalar::all(0), Scalar::all(KF.measurementNoiseCov.at<float>(0))); //��measurement��ֵN(0,R)�����ֵ
//
//																							      // generate measurement
//			measurement += KF.measurementMatrix*state;  //z = z + H*x;
//
//			double measAngle = measurement.at<float>(0);
//			Point measPt = calcPoint(center, R, measAngle);
//
//			// plot points
//			//�����˻�ʮ�ֵķ�����ֵ��ѧϰ��
//               #define drawCross( center, color, d )                                 \
//                line( img, Point( center.x - d, center.y - d ),                \
//                             Point( center.x + d, center.y + d ), color, 1, CV_AA, 0); \
//                line( img, Point( center.x + d, center.y - d ),                \
//                             Point( center.x - d, center.y + d ), color, 1, CV_AA, 0 )
//
//			img = Scalar::all(0);
//			drawCross(statePt, Scalar(255, 255, 255), 3);
//			drawCross(measPt, Scalar(0, 0, 255), 3);
//			drawCross(predictPt, Scalar(0, 255, 0), 3);
//			cv::imshow("test", img);
//			cv::waitKey(0);
//			line(img, statePt, measPt, Scalar(0, 0, 255), 3, CV_AA, 0);
//			line(img, statePt, predictPt, Scalar(0, 255, 255), 3, CV_AA, 0);
//
//			//cv::imshow("test", img);
//			//cv::waitKey(0);
//
//			//����kalman������correct�����õ�����۲�ֵУ�����״̬����ֵ����
//			if (theRNG().uniform(0, 4) != 0)
//				KF.correct(measurement);
//
//			//���������Ļ���������Բ���˶������˵�������������Բ���˶�����Ϊ������ԭ���˶�������ܻ�ı�
//			randn(processNoise, Scalar(0), Scalar::all(sqrt(KF.processNoiseCov.at<float>(0, 0))));   //vk
//			state = KF.transitionMatrix*state + processNoise;
//
//			imshow("Kalman", img);
//			code = (char)waitKey(100);
//
//			if (code > 0)
//				break;
//		}
//		if (code == 27 || code == 'q' || code == 'Q')
//			break;
//	}
//
//	return 0;
//}

#include <cv.h>  
#include <cxcore.h>  
#include <highgui.h>  
#include <cmath>  
#include <vector>  
#include <iostream>  
#include<opencv2\highgui.hpp>
#include<opencv2\core.hpp>
using namespace std;
const int winHeight = 600;
const int winWidth = 800;
CvPoint mousePosition = cvPoint(winWidth >> 1, winHeight >> 1);
//mouse event callback  
void mouseEvent(int event, int x, int y, int flags, void *param)
{
	if (event == CV_EVENT_MOUSEMOVE) {
		mousePosition = cvPoint(x, y);
	}
}
int main(void)
{
	//1.kalman filter setup  
	const int stateNum = 4;
	const int measureNum = 2;
	CvKalman* kalman = cvCreateKalman(stateNum, measureNum, 0);//state(x,y,detaX,detaY)  
	CvMat* process_noise = cvCreateMat(stateNum, 1, CV_32FC1);
	CvMat* measurement = cvCreateMat(measureNum, 1, CV_32FC1);//measurement(x,y)  
	CvRNG rng = cvRNG(-1);
	float A[stateNum][stateNum] = {//transition matrix  
		1,0,1,0,
		0,1,0,1,
		0,0,1,0,
		0,0,0,1
	};

	/*
	Mat statePre;            //Ԥ��ֵ (x'(k)): x(k)=A*x(k-1)+B*u(k)
	Mat statePost;           //״ֵ̬ (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
	Mat transitionMatrix;    //״̬ת�ƾ��� (A)
	Mat controlMatrix;       //���ƾ��� B 
	Mat measurementMatrix;   //�������� H
	Mat processNoiseCov;     //ϵͳ��� Q
	Mat measurementNoiseCov; //������� R
	Mat errorCovPre;         //��С������� (P'(k)): P'(k)=A*P(k-1)*At + Q)
	Mat gain;                //����������   (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
	Mat errorCovPost;        //��������С������� (P(k)): P(k)=(I-K(k)*H)*P'(k)
	*/
	memcpy(kalman->transition_matrix->data.fl, A, sizeof(A));
	cvSetIdentity(kalman->measurement_matrix, cvRealScalar(1));//��������H
	cvSetIdentity(kalman->process_noise_cov, cvRealScalar(1e-5));//ϵͳ���Q
	cvSetIdentity(kalman->measurement_noise_cov, cvRealScalar(1e-1));//�������R
	cvSetIdentity(kalman->error_cov_post, cvRealScalar(1));//���������С�������
	//initialize post state of kalman filter at random  
	cvRandArr(&rng, kalman->state_post, CV_RAND_UNI, cvRealScalar(0), cvRealScalar(winHeight > winWidth ? winWidth : winHeight));
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SCRIPT_COMPLEX, 1, 1);
	cvNamedWindow("kalman");
	cvSetMouseCallback("kalman", mouseEvent);
	IplImage* img = cvCreateImage(cvSize(winWidth, winHeight), 8, 3);
	while (1) {
		//2.kalman prediction  
		const CvMat* prediction = cvKalmanPredict(kalman, 0);
		CvPoint predict_pt = cvPoint((int)prediction->data.fl[0], (int)prediction->data.fl[1]);
		//3.update measurement  
		measurement->data.fl[0] = (float)mousePosition.x;
		measurement->data.fl[1] = (float)mousePosition.y;
		//4.update  
		const CvMat* optimal = cvKalmanCorrect(kalman, measurement);
		CvPoint optimal_pt = cvPoint((int)optimal->data.fl[0], (int)optimal->data.fl[1]);
		//draw 
		//cvShowImage("ori", img);
		//cv::waitKey(0);
		cvSet(img, cvScalar(255, 255, 255, 0));
		//cvShowImage("set", img);
		//cv::waitKey(0);
		cvCircle(img, predict_pt, 5, CV_RGB(0, 255, 0), 3);//predicted point with green  
		cvCircle(img, optimal_pt, 5, CV_RGB(0, 0,255), 3);
		cvCircle(img, mousePosition, 5, CV_RGB(255, 0, 0), 3);//current position with red  
		//cvShowImage("kalman", img);
		//int key = cvWaitKey(3);
		char buf[256];
		sprintf_s(buf, 256, "predicted position:(%3d,%3d)", predict_pt.x, predict_pt.y);
		cvPutText(img, buf, cvPoint(10, 30), &font, CV_RGB(0, 0, 0));
		sprintf_s(buf, 256, "optimal position:(%3d,%3d)", optimal_pt.x, optimal_pt.y);
		cvPutText(img, buf, cvPoint(10, 60), &font, CV_RGB(0, 0, 0));
		sprintf_s(buf, 256, "current position :(%3d,%3d)", mousePosition.x, mousePosition.y);
		cvPutText(img, buf, cvPoint(10, 90), &font, CV_RGB(0, 0, 0));

		cvShowImage("kalman", img);
		int key = cvWaitKey(3);
		if (key == 27) {//esc     
			break;
		}
	}
	cvReleaseImage(&img);
	cvReleaseKalman(&kalman);
	return 0;
}