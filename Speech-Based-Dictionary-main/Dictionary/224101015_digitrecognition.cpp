// 224101015_digitrecognition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

#define N 5
#define M 32
int T = 0;
int live_train_words;
long double pi[N + 1] = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0};
long double A[N + 1][N + 1] = {0.0};
long double B[N + 1][M + 1] = {0.0};
long double Alpha[150][N + 1] = {0.0};
long double Beta[150][N + 1] = {0.0};
long double Gamma[150][N + 1] = {0.0};
long double Delta[150][N + 1] = {0.0};
int Psi[150][N + 1] = {0};
long double Xi[150][N + 1][N + 1] = {0.0};
long double pi_bar[N + 1] = {0.0};
long double A_bar[N + 1][N + 1] = {0.0};
long double B_bar[N + 1][M + 1] = {0.0};
long double Avg_pi[10][N + 1] = {0.0};
long double Avg_A[10][N + 1][N + 1] = {0.0};
long double Avg_B[10][N + 1][M + 1] = {0.0};
long double P[100] = {0.0};
long double Pstar = 0;
int qstar[155] = {0};
int O[160] = {0};
long double codebook[33][13] = {0};
long double sample[500000] = {0.0};
int n = 0;
int p = 12;
int q = 12;
long double r[13] = {0.0};
long double a[13] = {0.0};
long double c[13] = {0.0};
long double frame_ci[150][13] = {0.0};
long double tokhura_weights[13] = {0.0, 1.0, 3.0, 7.0, 13.0, 14.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
long double dist_cepstral[50] = {0.0};
long double ct[13] = {0.0};
int num_correct_outputs = 0;
long double overall_accuracy = 0.0;
long double accuracy_per_digit[10] = {0.0};
FILE *write_p_values = fopen("p_values.txt", "w");
int findstart(long double sample[], int n)
{
    long double prevEnergy = -1, currentEnergy = 0;
    int count = 0;
    int i;
    for (i = 0; i < n; i += 320)
    {
        count = 0;

        while (count < 320)
        {
            currentEnergy += sample[i + count] * sample[i + count];
            count++;
        }
        currentEnergy /= 320;

        if (prevEnergy != -1 && currentEnergy >= 2.5 * prevEnergy)
        {

            return i;
        }
        else
            prevEnergy = currentEnergy;
    }
}

int findend(long double sample[], int n)
{
    long double prevEnergy = -1, currentEnergy = 0;
    int count = 0;
    int i;
    for (i = n - 1; i >= 0; i -= 320)
    {
        count = 0;

        while (count < 320)
        {
            currentEnergy += sample[i - count] * sample[i - count];
            count++;
        }
        currentEnergy /= 320;

        if (prevEnergy != -1 && currentEnergy == 3 * prevEnergy)
        {

            return i - 320;
        }
        else
            prevEnergy = currentEnergy;
    }
}
// Resets the values of variables required in accuracy calculation
void reset_acc_calculations()
{
    int i;
    for (i = 0; i <= 4; i++)
    {
        accuracy_per_digit[i] = 0.0;
    }
    overall_accuracy = 0.0;
    num_correct_outputs = 0;
}

//	Load the codebook
void read_codebook()
{
    FILE *myFile = fopen("codebook.txt", "r");
    int i, j;
    if (myFile == NULL)

    {
        printf("Codeook can't be read\n");
    }
    else
    {
        while (!feof(myFile))
        {
            for (i = 1; i <= 32; i++)
            {
                for (j = 1; j <= 12; j++)
                {
                    fscanf(myFile, "%lf", &codebook[i][j]);
                }
            }
        }
    }

    fclose(myFile);
}

//	Loads the initial model
void load_initial_model()
{
    FILE *myFile = fopen("A_initial.txt", "r"); // It reads initial A matrix
    int i, j;

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            fscanf(myFile, "%Lf", &A[i][j]);
        }
    }
    fclose(myFile);

    myFile = fopen("B_initial.txt", "r"); // it reads initial B matrix

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
        {
            fscanf(myFile, "%Lf", &B[i][j]);
        }
    }
    fclose(myFile);
}

//	Loads the average model for a particular digit
void load_average_model(int digit, int iter)
{
    int i, j;
    char filename[100];
    // lambda folder stores the model values
    sprintf(filename, "lambdas/digit%d_A%d_matrix.txt", digit, iter);
    FILE *myFile = fopen(filename, "r");

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            fscanf(myFile, "%Le", &A[i][j]);
        }
    }
    fclose(myFile);

    sprintf(filename, "lambdas/digit%d_B%d_matrix.txt", digit, iter);
    myFile = fopen(filename, "r");

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
        {
            fscanf(myFile, "%Le", &B[i][j]);
        }
    }
    fclose(myFile);
}

//	resets the model to zero to be on safer side
void reset_model()
{
    int i, j;
    for (i = 1; i <= N; i++)
    {
        pi_bar[i] = 0;
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            A_bar[i][j] = 0;
        }
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
        {
            B_bar[i][j] = 0;
        }
    }
}

//	Perform DC shift and normalization on the recorded data
void preprocess(long double arr[], int n)
{
    long double peak_value = fabs(arr[0]);
    int i;
    for (i = 0; i < n; i++)
    { // if current valus is larger than the peak_value then update peak_value
        if (fabs(arr[i]) > peak_value)
        {
            peak_value = fabs(arr[i]);
        }
    }
    // normalization factor calculated from peak_value
    long double normalization_factor = 5000.0 / peak_value, dcvalue = 0.0;

    i = 0;
    while (i < 100)
    { // sum values to get dc shift value
        dcvalue += arr[i];
        i++;
    }
    dcvalue /= (long double)100;

    for (i = 0; i < n; i++)
    {
        arr[i] -= dcvalue;
        arr[i] *= normalization_factor;
    }
}

//	Computes Ri values and store in R array
void Ricalculation(long double arr[], long double R[])
{
    int i, j;

    for (i = 0; i <= p; i++)
    {
        R[i] = 0;
        for (j = 0; j <= 314 - i; j++)
        {
            R[i] += arr[j] * arr[i + j];
        }
    }
}

//	Compute Ai values and save in a array
void Aicalculation(long double r[], long double a[])
{
    long double e[13];
    long double k[13];
    long double x[13][13];
    int i, j;
    long double s = 0.0;

    e[0] = r[0];

    for (i = 1; i <= p; i++)
    {
        for (j = 1; j <= i - 1; j++)
        {
            s += x[i - 1][j] * r[i - j];
        }
        k[i] = (r[i] - s) / e[i - 1];
        x[i][i] = k[i];

        for (j = 1; j <= (i - 1); j++)
        {
            x[i][j] = x[i - 1][j] - k[i] * x[i - 1][i - j];
        }
        e[i] = (1 - k[i] * k[i]) * e[i - 1];
        s = 0.0;
    }

    for (i = 1; i <= p; i++)
    {
        a[i] = x[p][i];
    }
}

//	Compute Ci values and store this is c array
void Cicalculation(long double a[], long double c[])
{
    long double s = 0.0;
    int i, j;
    c[0] = log10(r[0] * r[0]);

    for (i = 1; i <= p; i++)
    {
        for (j = 1; j <= i - 1; j++)
        {
            s += ((long double)j / (long double)i) * c[j] * a[i - j];
        }
        c[i] = a[i] + s;
        s = 0;
    }
}

//	Calculates the tokhura distance and create the observation sequence
void oservationseqbythokura(long double ct[150][13])
{
    int i, j, t;
    for (t = 1; t <= T; t++)
    {
        for (i = 1; i <= 32; i++)
        {
            long double dist = 0;
            for (j = 1; j <= 12; j++)
            {
                dist += tokhura_weights[j] * (ct[t][j] - codebook[i][j]) * (ct[t][j] - codebook[i][j]);
            }
            dist_cepstral[i] = dist;
        }

        long double min_val = dist_cepstral[1];
        int min_idx = 1;
        for (i = 2; i <= 32; i++)
        {
            if (dist_cepstral[i] < min_val)
            {
                min_val = dist_cepstral[i];
                min_idx = i;
            }
        }
        O[t] = min_idx; // save the sequence number of current frame into the observation array
    }
}

//	Computes the Alpha matrix
void forward()
{
    long double Prob = 0.0;
    int i, j, t;
    // alpha matrix is initialized
    for (i = 1; i <= N; i++)
    {
        Alpha[1][i] = pi[i] * B[i][O[1]];
    }
    // create alpha matrix
    for (t = 1; t <= T - 1; t++)
    {
        for (j = 1; j <= N; j++)
        {
            long double sum = 0.0;
            for (i = 1; i <= N; i++)
            {
                sum += Alpha[t][i] * A[i][j];
            }
            Alpha[t + 1][j] = sum * B[j][O[t + 1]];
        }
    }

    for (int i = 1; i <= N; i++)
    {
        Prob += Alpha[T][i];
    }
}

//	Computes the Beta matrix
void backward()
{
    int i, j, t;
    for (i = 1; i <= N; i++)
    {
        Beta[T][i] = 1.0;
    }

    for (t = T - 1; t >= 1; t--)
    {
        for (i = 1; i <= N; i++)
        {
            long double sum = 0;
            for (j = 1; j <= N; j++)
            {
                sum += A[i][j] * B[j][O[t + 1]] * Beta[t + 1][j];
            }
            Beta[t][i] = sum;
        }
    }
}

//	computes the Gamma matrix
void gammacalculate()
{
    int i, j, t;
    for (t = 1; t <= T; t++)
    {
        for (j = 1; j <= N; j++)
        {
            long double numerator = Alpha[t][j] * Beta[t][j];
            long double denominator = 0.0;
            for (i = 1; i <= N; i++)
            {
                denominator += Alpha[t][i] * Beta[t][i];
            }
            Gamma[t][j] = numerator / denominator;
        }
    }
}

//	Vitarbi Algorithm
void vitarbialgorithm()
{
    int i, j, t;

    //	Initialization
    for (i = 1; i <= N; i++)
    {
        Delta[1][i] = pi[i] * B[i][O[1]];
        Psi[1][i] = 0;
    }

    // Recursion
    for (t = 2; t <= T; t++)
    {
        for (j = 1; j <= N; j++)
        {
            long double temp = 0.0, currmax = 0.0;
            int idx = 0;
            for (i = 1; i <= N; i++)
            {
                temp = Delta[t - 1][i] * A[i][j];
                if (temp >= currmax)
                {
                    currmax = temp;
                    idx = i;
                }
            }
            Delta[t][j] = currmax * B[j][O[t]];
            Psi[t][j] = idx;
        }
    }

    // Termination
    long double currmax = 0.0;
    for (i = 1; i <= N; i++)
    {
        long double temp = Delta[T][i];
        if (temp >= currmax)
        {
            currmax = temp;
            qstar[T] = i;
        }
        Pstar = currmax;
    }

    //	Path Backtracking
    for (t = T - 1; t >= 1; t--)
    {
        qstar[t] = Psi[t + 1][qstar[t + 1]];
    }
}

void reestimate()
{
    int i, j, t, k;

    for (t = 1; t <= T; t++)
    {
        long double sum = 0.0;
        for (i = 1; i <= N; i++)
        {
            for (j = 1; j <= N; j++)
            {
                sum += Alpha[t][i] * A[i][j] * B[j][O[t + 1]] * Beta[t + 1][j];
            }
        }
        for (i = 1; i <= N; i++)
        {
            for (j = 1; j <= N; j++)
            {
                Xi[t][i][j] = Alpha[t][i] * A[i][j] * B[j][O[t + 1]] * Beta[t + 1][j] / sum;
            }
        }
    }

    for (i = 1; i <= N; i++)
    {
        pi[i] = Gamma[1][i];
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            long double numerator = 0.0, denominator = 0.0;
            for (t = 1; t <= T - 1; t++)
            {
                numerator += Xi[t][i][j];
                denominator += Gamma[t][i];
            }
            A[i][j] = numerator / denominator;
        }
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
        {
            long double numerator = 0.0, denominator = 0.0;

            for (t = 1; t <= T; t++)
            {
                if (O[t] == j)
                {
                    numerator += Gamma[t][i];
                }
                denominator += Gamma[t][i];
            }

            B[i][j] = numerator / denominator;
        }
    }
}

//	Makes B stocahstic if its not a stochastic matrix
void make_B_Stochastic()
{
    int i, j;
    for (i = 1; i <= N; i++)
    {
        int num_zeros_num_correct_outputs = 0;
        long double max_val = 0.0;
        int max_val_idx = 0;

        for (j = 1; j <= M; j++)
        {
            if (B[i][j] > max_val)
            {
                max_val = B[i][j];
                max_val_idx = j;
            }
            if (B[i][j] == 0)
            {
                num_zeros_num_correct_outputs++;
                B[i][j] = pow(10.0, -30); // put 10^-30 when B value becomes zero
            }
        }
        B[i][max_val_idx] -= num_zeros_num_correct_outputs * pow(10.0, -30);
    }
}

//	Saves the model into files
void save_model(int k, int iter)
{
    int i, j;
    char filename[100];
    // models are stord inside a folder called lambda
    sprintf(filename, "lambdas/digit%d_A%d_matrix.txt", k, (iter + 1));
    FILE *myFile = fopen(filename, "w");
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            fprintf(myFile, "%Le\t", Avg_A[k][i][j]);
        }
        fprintf(myFile, "\n");
    }
    fclose(myFile);

    sprintf(filename, "lambdas/digit%d_B%d_matrix.txt", k, (iter + 1));
    myFile = fopen(filename, "w");

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
        {
            fprintf(myFile, "%Le\t", Avg_B[k][i][j]);
        }
        fprintf(myFile, "\n");
    }
    fclose(myFile);
}

//	Gives model for each utterance
void get_models()
{
    int i, j;
    for (i = 1; i <= 20; i++)
    {
        forward();
        backward();
        gammacalculate();
        vitarbialgorithm();
        reestimate();
        make_B_Stochastic();
    }
    make_B_Stochastic(); // apply again make_B_stochastic just to be on safer side

    for (i = 1; i <= N; i++)
    {
        pi_bar[i] += pi[i]; // keep on summing because later we neew average
    }

    for (i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            A_bar[i][j] += A[i][j]; // keep on summing because later we neew average
        }
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
        {
            B_bar[i][j] += B[i][j]; // keep on summing because later we neew average
        }
    }
}

//	Gives average model for each digit
void average(int d)
{
    int i, j;

    for (i = 1; i <= N; i++)
    {
        pi_bar[i] /= 20; // take avergare of 20 training data
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            A_bar[i][j] /= 20; // take avergare of 20 training data
        }
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
        {
            B_bar[i][j] /= 20; // take avergare of 20 training data
        }
    }
    // below loops stores the final avg value of each digit d
    for (i = 1; i <= N; i++)
    {
        Avg_pi[d][i] = pi_bar[i];
    }

    // below loops stores the final A ,avg value of  each digit d
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            Avg_A[d][i][j] = A_bar[i][j];
        }
    }
    // below loops stores the final B,avg value of each digit d
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
        {
            Avg_B[d][i][j] = B_bar[i][j];
        }
    }
}
//training of live data
void train_live(int time)
{
    printf("Training... iteration %d\n", time);
	for (int i = 0; i <live_train_words ; i++) //	10 digit
    {
        reset_model();
        for (int j = 0; j <= 19; j++) // 20 utterances of each training digit
        {

            if (time == 1)
            {
                load_initial_model(); // 1st time read the initial model
            }
            else
            {
                load_average_model(i, time);
            }

            char filename[100];
            // Recording file stores the recorder files
            sprintf(filename, "LiveTrain/digit%d_%d.txt", i, j);

            FILE *myFile = fopen(filename, "r");

            if (myFile != NULL)
            {
                n = 0;
                while (!feof(myFile))
                { // sample array stores the signal
                    fscanf(myFile, "%lf", &sample[n]);
                    n++;
                }
            }
            else
                printf("\nTrain Files cannot be opened %d %d ", i, j);
            fclose(myFile);
            // preprocess the sample array , normalisation and dc shift is done
            preprocess(sample, n);
            int f = findstart(sample, n);
            int e = findend(sample, n);
            int num_frames = 0;
            // this frame stores the 320 samples
            long double current_frame[320];
            // drops 1st 8000 samples and starts storing
            for (int bi = 1, k = f; k < f + (320 * 145) && k < n - 5000; bi++, k += 320)
            { // counts number of frame
                num_frames++;
                for (int y = 0; y < 320; y++)
                {
                    current_frame[y] = sample[y + k];
                }

                Ricalculation(current_frame, r); // ri calculated of the current frame
                Aicalculation(r, a);             // ai calculated of the current frame
                Cicalculation(a, c);             // ci calculated of the current frame

                for (int j = 1; j <= 12; j++)
                {
                    frame_ci[bi][j] = c[j]; // ith row says ith digit

                    // raised sine window is applied on the sample
                    frame_ci[bi][j] *= (1 + (6.0 * sin((3.14 * j) / 12.0)));
                }
            }
            T = num_frames; // T stores number of available frames
            // this below function computes the the observation sequence of the current frame
            oservationseqbythokura(frame_ci);
            // it computes lamda of the current digit
            get_models();
        }
        average(i); // take average lambdas of ith digit

        /*
        save model of ith digit and write the time it says the
        iteration number in which we got the current model

        */
        save_model(i, time);
    }
}


//	Training , iteration says the iteration number if 1 then we will load initial model
void train(int time)
{
    printf("Training... iteration %d\n", time);
    for (int i = 0; i <= 4; i++) //	10 digit
    {
        reset_model();
        for (int j = 0; j <= 19; j++) // 20 utterances of each training digit
        {

            if (time == 1)
            {
                load_initial_model(); // 1st time read the initial model
            }
            else
            {
                load_average_model(i, time);
            }

            char filename[100];
            // Recording file stores the recorder files
            sprintf(filename, "Recordings/digit%d_%d.txt", i, j);

            FILE *myFile = fopen(filename, "r");

            if (myFile != NULL)
            {
                n = 0;
                while (!feof(myFile))
                { // sample array stores the signal
                    fscanf(myFile, "%lf", &sample[n]);
                    n++;
                }
            }
            else
                printf("\nTrain Files cannot be opened %d %d ", i, j);
            fclose(myFile);
            // preprocess the sample array , normalisation and dc shift is done
            preprocess(sample, n);
            int f = findstart(sample, n);
            int e = findend(sample, n);
            int num_frames = 0;
            // this frame stores the 320 samples
            long double current_frame[320];
            // drops 1st 8000 samples and starts storing
            for (int bi = 1, k = f; k < f + (320 * 145) && k < n - 5000; bi++, k += 320)
            { // counts number of frame
                num_frames++;
                for (int y = 0; y < 320; y++)
                {
                    current_frame[y] = sample[y + k];
                }

                Ricalculation(current_frame, r); // ri calculated of the current frame
                Aicalculation(r, a);             // ai calculated of the current frame
                Cicalculation(a, c);             // ci calculated of the current frame

                for (int j = 1; j <= 12; j++)
                {
                    frame_ci[bi][j] = c[j]; // ith row says ith digit

                    // raised sine window is applied on the sample
                    frame_ci[bi][j] *= (1 + (6.0 * sin((3.14 * j) / 12.0)));
                }
            }
            T = num_frames; // T stores number of available frames
            // this below function computes the the observation sequence of the current frame
            oservationseqbythokura(frame_ci);
            // it computes lamda of the current digit
            get_models();
        }
        average(i); // take average lambdas of ith digit

        /*
        save model of ith digit and write the time it says the
        iteration number in which we got the current model

        */
        save_model(i, time);
    }
}
// this function is used to compute scoring prolem
void forward_test(int actual_digit)
{
    int i, j, t, k;
    for (k = 0; k <= 4; k++)
    {
        long double Prob = 0.0;

        for (i = 1; i <= N; i++)
        { // alpha is initialized for the digit k
            Alpha[1][i] = Avg_pi[k][i] * Avg_B[k][i][O[1]];
        }
        // alpha matris is computed for digit k
        for (t = 1; t <= T - 1; t++)
        {
            for (j = 1; j <= N; j++)
            {
                long double sum = 0.0;
                for (i = 1; i <= N; i++)
                {
                    sum += Alpha[t][i] * Avg_A[k][i][j];
                }
                Alpha[t + 1][j] = sum * Avg_B[k][j][O[t + 1]];
            }
        }

        for (int i = 1; i <= N; i++)
        {
            Prob += Alpha[T][i];
        }
        // probability that the data is kth digit
        P[k] = Prob;
    }

    long double max_val = P[0];
    int max_idx = 0;

    for (i = 1; i <= 4; i++)
    { // check the max probability
        if (P[i] > max_val)
        {
            max_val = P[i];
            // when max probability is found then max index is updated
            max_idx = i;
        }
    }
    // print the digit that is predicted
    printf("%d ", max_idx);
    // print pstar value corresponding to each digit
    for (i = 0; i <= 4; i++)
    {
        fprintf(write_p_values, "P value for %d is - %0.32Le\n", i, P[i]);
    }
    fprintf(write_p_values, "\nActual digit : %d, Predicted digit : %d\n", actual_digit, max_idx);

    fprintf(write_p_values, "--------------------------------------------------------\n\n");
    // if the actual digit and predicted digit matches
    if (max_idx == actual_digit)
    {
        // increase the correct prediction
        num_correct_outputs++;
        // accuracy per digit is stored
        accuracy_per_digit[actual_digit] += 1.0;
    }
}

//	Testing using pre-recorded data (seen data)
void test()
{
    printf("Testing with train data :-\n");

    reset_acc_calculations();
    for (int i = 0; i <= 4; i++)
    {
        printf("\nFor Digit %d:\n", i);
        for (int j = 0; j <= 19; j++)
        {
            char filename[100];
            // take data from recording folder
            sprintf(filename, "Recordings/digit%d_%d.txt", i, j);

            FILE *myFile = fopen(filename, "r");

            int num = 0;
            if (myFile != NULL)
            {
                while (!feof(myFile))
                { // store data in an array called sample
                    fscanf(myFile, "%lf", &sample[num++]);
                }
            }
            else
            {
                printf("\nTest Files cannot be opened");
            }
            fclose(myFile);
            // preprocess the sample data
            preprocess(sample, num);
            int f = findstart(sample, num);
            int e = findend(sample, num);
            int num_frames = 0;
            // this frame takes every frame and moves with operations
            long double current_frame[320];

            // drop 1st 8000 samples from test data
            for (int bi = 1, k = f; k < f + (320 * 140) && k < num - 5000; bi++, k += 320)
            {
                num_frames++;
                for (int lmk = 0; lmk < 320; lmk++)
                {
                    current_frame[lmk] = sample[lmk + k];
                }

                Ricalculation(current_frame, r); // ri values are calculated
                Aicalculation(r, a);             // ai values are calculated
                Cicalculation(a, c);             // ci values are calculated

                for (int j = 1; j <= 12; j++)
                {
                    frame_ci[bi][j] = c[j]; // ith test digit's cepstral vector is stored
                                            // raised sine window is applied
                    frame_ci[bi][j] *= (1 + (6.0 * sin((3.14 * j) / 12.0)));
                }
            }
            // number of frames is updated
            T = num_frames;
            // this function creates observation sequence using thokura distances
            oservationseqbythokura(frame_ci);
            // pstar values is stored for each digit
            fprintf(write_p_values, "For file %s\n", filename);
            // it prints the value of the pstar in the file pointed by write_p_values
            forward_test(i);
        }
    }

    printf("\n");
    for (int i = 0; i <= 4; i++)
    {
        accuracy_per_digit[i] /= 20.0; // average accuracy per digit is stored
        accuracy_per_digit[i] *= 100.0;
        // accuracy of the digit is printed
        printf("\nAccuracy for digit %d is %.2lf %%", i, accuracy_per_digit[i]);
    }
    // it prints the overall accuracy
    overall_accuracy = (num_correct_outputs * 100.0) / 100.0;

    printf("\nOverall overall_accuracy: %.2lf %%\n", overall_accuracy);
}

//	Testing using pre-recorded data (unseen data)
void test_offline()
{
    reset_acc_calculations();

    printf("Testing with Test data :-\n");
    for (int i = 0; i <= 4; i++)
    {
        printf("\nFor Digit %d:\n", i);
        for (int j = 20; j <= 29; j++)
        {
            char filename[100];
            // printf("i =%d j= %d \n",i,j);
            // test data is stored in the directory Recordings/test_data
            sprintf(filename, "Recordings/digit%d_%d.txt", i, j);
            // printf("%s ",filename);
            FILE *myFile = fopen(filename, "r");

            int num = 0;
            if (myFile == NULL)
            {
                printf("\nTest Files cannot be opened");
            }
            else
            {
                while (!feof(myFile))
                { // speech is store in sample array
                    fscanf(myFile, "%lf", &sample[num++]);
                }
            }
            fclose(myFile);

            // preprocessing is done normalisation and dc shift
            preprocess(sample, num);

            int num_frames = 0;
            // this frame stores the current frame
            long double current_frame[320];
            int f = findstart(sample, num);
            int e = findend(sample, num);
            // drop 1st 8000 samples
            for (int bi = 1, k = f; k < f + (320 * 140) && k < num - 5000; bi++, k += 320)
            {
                num_frames++;
                for (int lmk = 0; lmk < 320; lmk++)
                {
                    current_frame[lmk] = sample[lmk + k];
                }

                Ricalculation(current_frame, r); // ri calculations of the current frame
                Aicalculation(r, a);             // ai calculations of the current frame
                Cicalculation(a, c);             // ci calculations of the current frame

                for (int j = 1; j <= 12; j++)
                {
                    frame_ci[bi][j] = c[j]; // ith digit stores the cepstral vectors
                    // raised sine window is applied
                    frame_ci[bi][j] *= (1 + (6.0 * sin((3.14 * j) / 12.0)));
                }
            }

            T = num_frames; // number of frames are updated

            // oservation sequence is calculated using thokura dist
            oservationseqbythokura(frame_ci);
            // test for the scoring problem
            forward_test(i);
        }
    }

    printf("\n");
    for (int i = 0; i <= 4; i++)
    {
        accuracy_per_digit[i] /= 10.0; // accuracy avg is taken
        // prcent of accuracy is found
        accuracy_per_digit[i] *= 100.0;
        // accuracy of a digit is printed
        printf("\nAccuracy for digit %d is %.2lf %%", i, accuracy_per_digit[i]);
    }
    // overall accuracy is printed
    overall_accuracy = (num_correct_outputs * 100.0) / 50.0;

    printf("\nOverall overall_accuracy: %.2lf %%\n", overall_accuracy);
}

void live_train()
{
    char filename[50];
    // system(".\\Recording_module.exe 3 live_data.wav live_data.txt");
    for (int i = 4; i < live_train_words; i++)
    {
        printf("you are recording word number %d \n", i);
        for (int j = 0; j <= 29; j++)
        {
            printf("Word number %d make the utterence number %d ", i, j);
            system(".\\Recording_module.exe 2 live_data.wav live_data.txt");
            FILE *myFile = fopen("live_data.txt", "r");
            sprintf(filename, "Recordings/digit%d_%d.txt", i, j);
            FILE *file_write = fopen(filename, "w");
            if (myFile == NULL)
            {
                printf("\nLive data cannot be opened\n");
            }
            else
            {

                while (!feof(myFile))
                {
                    // values re stored inside sample array
                    double bits;
                    fscanf(myFile, "%lf", &bits);
                    fprintf(file_write, "%lf\n ", bits);
                }
            }
        }
    }

    printf("All words are recorded, Now training will be started please wait for few seconds \n");
	int b=0;
	for(b=1;b<=3;b++)
	{
		train_live(b);
	}

}

//	Testing using live data
void test_livedata()
{
    reset_acc_calculations(); // accuracy calculator is reset
    // live data is read and stored in live_data.txt
    system(".\\Recording_module.exe 3 live_data.wav live_data.txt");

    FILE *myFile = fopen("live_data.txt", "r");

    int num = 0;
    if (myFile == NULL)
    {
        printf("\nLive data cannot be opened");
    }
    else
    {

        while (!feof(myFile))
        {
            // values re stored inside sample array
            fscanf(myFile, "%lf", &sample[num++]);
        }
    }
    fclose(myFile);

    preprocess(sample, num); // dcshift and normalisation done
    int f = findstart(sample, num);
    int e = findend(sample, num);
    int num_frames = 0;
    long double current_frame[320]; // this stores the current frame

    // drrop 1st 8000 samples
    for (int i = 1, k = f; k < f + (320 * 140) && k < num - 5000; i++, k += 320)
    {
        num_frames++;
        for (int lmk = 0; lmk < 320; lmk++)
        {
            current_frame[lmk] = sample[lmk + k];
        }
        // ri calculations done
        Ricalculation(current_frame, r);
        // ai calculations done
        Aicalculation(r, a);
        // ci calculations done
        Cicalculation(a, c);

        for (int j = 1; j <= 12; j++)
        {
            frame_ci[i][j] = c[j]; // cepstral vector of ith digit is stored
            // raised sine window is applied
            frame_ci[i][j] *= (1 + (6.0 * sin((3.14 * j) / 12.0)));
        }
    }

    T = num_frames; // number of frames are stored in T

    // observation seq of live data is computed
    oservationseqbythokura(frame_ci);

    int i, j, t, k;
    for (k = 0; k <= 4; k++)
    {
        long double temp = 0;
        long double Prob = 0;
        // alpha is initialized
        for (i = 1; i <= N; i++)
        {
            // avg model of each digit is loaded
            Alpha[1][i] = Avg_pi[k][i] * Avg_B[k][i][O[1]];
        }
        // rest of the alpha matrix is computed for the live data
        for (t = 1; t <= T - 1; t++)
        {
            for (j = 1; j <= N; j++)
            {
                temp = 0;
                for (i = 1; i <= N; i++)
                {
                    temp += Alpha[t][i] * Avg_A[k][i][j];
                }
                temp *= Avg_B[k][j][O[t + 1]];
                Alpha[t + 1][j] = temp;
            }
        }

        for (i = 1; i <= N; i++)
        {
            Prob += Alpha[T][i];
        }
        P[k] = Prob; // probabilit that the live spoken digit is k
    }

    long double max = P[0];
    int maxindex = 0;
    // check which digit has highest probability
    for (i = 1; i <= 4; i++)
    {
        if (P[i] > max)
        {
            max = P[i];
            // when max prob is updated then max index is also updated
            maxindex = i;
        }
    }
    // recognized digit is printed
    printf("Recognized digit is - %d\n", maxindex);
}

int _tmain(int argc, _TCHAR *argv[])
{
    int i;
    // read codebook
    read_codebook();

    // train thrice
    for (i = 1; i <= 3; i++)
    {
        train(i);
    }

    int choice = -1;
    // below while loop creates the user driven menu
    while (choice)
    {
        printf("\nPress 0 to EXIT\nPress 1 to test with training data\nPress 2 to test with testing data\nPress 3 to test with live data\nPress 4 to record live data\nEnter your choice :- ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            test(); // when test on train data is required
            break;

        case 2:
            test_offline(); // test on testing data
            break;

        case 3:
            printf("When you see the text 'Start Recording...........', you will have 3 seconds to record the sound. When ready ");
            // this part is used when we need to go for the live data
            system("pause");
            // call the function to test live data
            test_livedata();
            break;

        case 0:
            printf("\nExiting the program !!!\n");
            break;
        case 4:
            printf("live training will start soon, enter number of words you want to train  \n ");
            scanf("%d", &live_train_words);

            system("pause");
            live_train();
            break;
        default:
            printf("Invalid choice!!! Enter a valid choice between 0 and 3.\n");
            // if user enters wrong choice
            break;
        }
    }

    fclose(write_p_values);

    // getch();

    return 0;
}